#include "materials/material-properties.h"
#include "imaging/color.h"


using namespace imaging;

raytracer::MaterialProperties::MaterialProperties(
    const Color& ambient,
    const Color& diffuse,
    const Color& specular,
    const double specular_exponent)
    : ambient(ambient)
    , diffuse(diffuse)
	, specular(specular)
	, specular_exponent(specular_exponent)
{
    // NOP
}

raytracer::MaterialPropertiesBuilder::MaterialPropertiesBuilder()
    : m_ambient(colors::black())
    , m_diffuse(colors::black())
	, m_specular(colors::black())
	, m_specular_exponent(1)
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

raytracer::MaterialPropertiesBuilder& raytracer::MaterialPropertiesBuilder::specular(const imaging::Color& color, const double exponent)
{
    m_specular = color;
    m_specular_exponent = exponent;

    return *this;
}

raytracer::MaterialPropertiesBuilder::operator raytracer::MaterialProperties() const
{
    return MaterialProperties(
        m_ambient,
        m_diffuse,
        m_specular,
        m_specular_exponent
    );
}
