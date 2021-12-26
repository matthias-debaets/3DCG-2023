#include "primitives/mesh/mesh-primitive.h"
#include "mesh-receiver.h"
#include "primitives/triangle-primitive.h"
#include "primitives/bbacc.h"
#include "primitives/union-primitive.h"
#include <fstream>
#include "easylogging++.h"
#include "primitives/mesh/mesh-text-reader.h"


using namespace raytracer;
using namespace raytracer::primitives;

namespace 
{
	class MeshReceiverImplementation : public raytracer::primitives::MeshReceiver
	{
	private:
        std::vector<math::Point3D> points;
        std::vector<Primitive> primitives;
	public:
		/// <summary>
		/// Called for each vertex in the mesh.
		/// </summary>
		/// <param name="x">X-coordinate</param>
		/// <param name="y">Y-coordinate</param>
		/// <param name="z">Z-coordinate</param>
        void vertex(double x, double y, double z) override
        {
            const auto point = math::Point3D(x, y, z);
            points.push_back(point);
        }
		
		/// <summary>
		/// Called for each normal in the mesh.
		/// </summary>
		/// <param name="x">X-coordinate</param>
		/// <param name="y">Y-coordinate</param>
		/// <param name="z">Z-coordinate</param>
        void normal(double x, double y, double z) override
        {
	        
        }

        /// <summary>
        /// Called for each triangle in the mesh.
        /// </summary>
        /// <param name="vertex1">Index of first vertex</param>
        /// <param name="vertex2">Index of second vertex</param>
        /// <param name="vertex3">Index of third vertex</param>
        void triangle(unsigned vertex1, unsigned vertex2, unsigned vertex3) override
        {
            const auto triangle = primitives::triangle(points[vertex1], points[vertex2], points[vertex3]);
            primitives.push_back(triangle);
        }

        /// <summary>
        /// Called for each box in the mesh.
        /// </summary>
        /// <param name="n_children">Number of children in the box</param>
        void box(unsigned n_children) override
        {
            std::vector<Primitive> children;
	        for (unsigned i = 0; i < n_children; i++)
	        {
                auto child = primitives.back();
                primitives.pop_back();
                children.push_back(child);
	        }
            const auto u = primitives::make_union(children);
            const auto box = primitives::bounding_box_accelerator(u);
            primitives.push_back(box);
        }

		Primitive mesh_reader()
        {
            return primitives.back();
        }
	};
}

Primitive primitives::mesh(const std::string& path)
{
    std::ifstream file;
	file.open(path);
	CHECK(file.is_open()) << "Failed to open file at " + path;
    auto mesh_receiver = MeshReceiverImplementation();
    raytracer::primitives::read_text_mesh(file, mesh_receiver);
    return mesh_receiver.mesh_reader();
	
}


