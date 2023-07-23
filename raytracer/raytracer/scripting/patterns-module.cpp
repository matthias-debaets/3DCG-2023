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
        Pattern2D constant2d(bool value) const
        {
	        return patterns::constant2d(value);
		}

        Pattern3D constant3d(bool value) const
        {
	        return patterns::constant3d(value);
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
    BIND(constant2d);
    BIND(constant3d);
#   undef BIND_AS
#   undef BIND

    return module;
}

#endif
