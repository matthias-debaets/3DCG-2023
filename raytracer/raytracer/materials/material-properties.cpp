#include "materials/material-properties.h"
#include "imaging/color.h"


using namespace imaging;

raytracer::MaterialProperties::MaterialProperties(
    const Color& ambient,
    const Color& diffuse)
    : ambient(ambient)
    , diffuse(diffuse)
{
    // NOP
}

raytracer::MaterialPropertiesBuilder::MaterialPropertiesBuilder()
    : m_ambient(colors::black())
    , m_diffuse(colors::black())
{
    // NOP
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::ambient(const imaging::Color& color)
{
    m_ambient = color;

    return *this;
}

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::diffuse(const imaging::Color& color)
{
    m_diffuse = color;

    return *this;
}

raytracer::MaterialPropertiesBuilder::operator raytracer::MaterialProperties() const
{
    return MaterialProperties(
        m_ambient,
        m_diffuse
    );
}
