#pragma once

#include "imaging/color.h"


namespace raytracer
{
    struct MaterialProperties
    {
    private:
        MaterialProperties(
            const imaging::Color& ambient,
            const imaging::Color& diffuse,
            const imaging::Color& specular,
            const double specular_exponent);

    public:
        const imaging::Color ambient;
        const imaging::Color diffuse;
        const imaging::Color specular;
        const double specular_exponent;

        friend class MaterialPropertiesBuilder;
    };

    class MaterialPropertiesBuilder
    {
    public:
        MaterialPropertiesBuilder();

        MaterialPropertiesBuilder& ambient(const imaging::Color& color);
        MaterialPropertiesBuilder& diffuse(const imaging::Color& color);
        MaterialPropertiesBuilder& specular(const imaging::Color& specular, const double specular_exponent);

        operator raytracer::MaterialProperties() const;

    private:
        imaging::Color m_ambient;
        imaging::Color m_diffuse;
        imaging::Color m_specular;
        double m_specular_exponent;
    };

    inline MaterialPropertiesBuilder create_material_properties_with()
    {
        return MaterialPropertiesBuilder();
    }
}