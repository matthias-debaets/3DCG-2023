#pragma once

#include "imaging/color.h"


namespace raytracer
{
    struct MaterialProperties
    {
    private:
        MaterialProperties(
            const imaging::Color& ambient,
            const imaging::Color& diffuse);

    public:
        const imaging::Color ambient;
        const imaging::Color diffuse;

        friend class MaterialPropertiesBuilder;
    };

    class MaterialPropertiesBuilder
    {
    public:
        MaterialPropertiesBuilder();

        MaterialPropertiesBuilder& ambient(const imaging::Color& color);
        MaterialPropertiesBuilder& diffuse(const imaging::Color& color);

        operator raytracer::MaterialProperties() const;

    private:
        imaging::Color m_ambient;
        imaging::Color m_diffuse;
    };

    inline MaterialPropertiesBuilder create_material_properties_with()
    {
        return MaterialPropertiesBuilder();
    }
}