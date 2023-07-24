#ifndef EXCLUDE_SCRIPTING

#include "scripting/patterns-module.h"
#include "scripting/scripting-util.h"
#include "patterns/patterns.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace patterns;


namespace
{
    struct PatternLibrary
    {
        Pattern2D xsplit2d(double boundary) const
        {
			return patterns::xsplit2d(boundary);
		}

        Pattern3D xsplit3d(double boundary) const
        {
	        return patterns::xsplit3d(boundary);
        }

        Pattern2D ysplit2d(double boundary) const
        {
	        return patterns::ysplit2d(boundary);
        }

        Pattern3D ysplit3d(double boundary) const
        {
	        return patterns::ysplit3d(boundary);
		}

        Pattern2D constant2d(bool value) const
        {
	        return patterns::constant2d(value);
		}

        Pattern3D constant3d(bool value) const
        {
	        return patterns::constant3d(value);
        }

        Pattern2D lines2d(double thickness, double spacing) const
        {
            return patterns::tiling_y(ysplit2d(thickness), thickness + spacing);
        }

        Pattern2D tiling2d(Pattern2D pattern, double width, double height) const
        {
	        return patterns::tiling(pattern, width, height);
		}

        Pattern3D tiling3d(Pattern3D pattern, double x_size, double y_size, double z_size) const
        {
			return patterns::tiling(pattern, x_size, y_size, z_size);
        }

        Pattern2D tiling_x(Pattern2D pattern, double width) const
        {
	        return patterns::tiling_x(pattern, width);
		}

        Pattern2D tiling_y(Pattern2D pattern, double height) const
        {
	        return patterns::tiling_y(pattern, height);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_patterns_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Pattern2D>(*module, "Pattern2D");
    util::register_type<Pattern3D>(*module, "Pattern3D");

    auto pattern_library = std::make_shared<PatternLibrary>();
    module->add_global_const(chaiscript::const_var(pattern_library), "Patterns");

#   define BIND(NAME)                      BIND_AS(NAME, NAME)
#   define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&PatternLibrary::INTERNAL), #EXTERNAL)
    BIND_AS(xsplit2d, xsplit);
    BIND_AS(xsplit3d, xsplit);
    BIND_AS(ysplit2d, ysplit);
    BIND_AS(ysplit3d, ysplit);
    BIND(constant2d);
    BIND(constant3d);
    BIND_AS(tiling2d, tiling);
    BIND_AS(tiling3d, tiling);
    BIND(tiling_x);
    BIND(tiling_y);
    BIND_AS(lines2d, lines);
#   undef BIND_AS
#   undef BIND

    return module;
}

#endif
