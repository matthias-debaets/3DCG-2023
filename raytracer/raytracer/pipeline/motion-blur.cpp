#include "motion-blur.h"

#include <memory>
#include <vector>

#include "processor.h"
#include "imaging/bitmap.h"

namespace 
{
    class MotionBlurProcessor : public raytracer::pipeline::Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<imaging::Bitmap>> {
    public:
        MotionBlurProcessor(unsigned frame_count, unsigned frame_offset)
            : m_frame_count(frame_count), m_frame_offset(frame_offset) { }

        void consume(std::shared_ptr<imaging::Bitmap> frame) override {
            if (m_subframes.size() < m_frame_count) {
                m_subframes.push_back(frame);
            }
            else {
                //m_subframes[m_frame_offset] = frame;
                std::shared_ptr<imaging::Bitmap> motion_blurred_frame = combine_subframes();
                produce(motion_blurred_frame);
                m_subframes.erase(m_subframes.begin(), m_subframes.begin() + m_frame_offset);
            }
        }

    private:
        unsigned m_frame_count;
        unsigned m_frame_offset;
        std::vector<std::shared_ptr<imaging::Bitmap>> m_subframes;

        std::shared_ptr<imaging::Bitmap> combine_subframes() {
            std::shared_ptr<imaging::Bitmap> motion_blurred_frame = std::make_shared<imaging::Bitmap>(m_subframes[0]->width(), m_subframes[0]->height());

            for (unsigned subframe_idx = 0; subframe_idx < m_frame_count; ++subframe_idx) {
                for (unsigned y = 0; y < motion_blurred_frame->height(); ++y) {
                    for (unsigned x = 0; x < motion_blurred_frame->width(); ++x) {
                        imaging::Color sum_color = imaging::Color(0,0,0);
                        for (const auto& subframe : m_subframes) {
                            sum_color += get_pixel(*subframe, x, y);
                        }
                        imaging::Color averaged_color = sum_color / m_frame_count;
                        set_pixel(*motion_blurred_frame, x, y, averaged_color);
                    }
                }
            }

            return motion_blurred_frame;
        }

        imaging::Color get_pixel(const imaging::Bitmap& original, unsigned x, unsigned y) {
            if (x >= 0 && x < original.width() && y >= 0 && y < original.height()) {
                return original[{static_cast<unsigned>(x), static_cast<unsigned>(y)}];
            }
            else {
                return imaging::Color(0, 0, 0);
            }
        }

        void set_pixel(imaging::Bitmap& new_bitmap, unsigned x, unsigned y, const imaging::Color& color) {
            if (x >= 0 && x < new_bitmap.width() && y >= 0 && y < new_bitmap.height()) {
                new_bitmap[{static_cast<unsigned>(x), static_cast<unsigned>(y)}] = color;
            }
        }

    };
}

std::shared_ptr<raytracer::pipeline::Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<imaging::Bitmap>>> raytracer::pipeline::motion_blur(unsigned frame_count, unsigned frame_offset)
{
	return std::make_shared<MotionBlurProcessor>(frame_count, frame_offset);
}