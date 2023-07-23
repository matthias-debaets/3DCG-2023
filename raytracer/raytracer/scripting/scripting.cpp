#include "patterns-module.h"
#ifndef EXCLUDE_SCRIPTING

#include "scripting/scripting.h"
#include "scripting/math-module.h"
#include "scripting/imaging-module.h"
#include "scripting/primitives-module.h"
#include "scripting/cameras-module.h"
#include "scripting/lights-module.h"
#include "scripting/raytracing-module.h"
#include "scripting/materials-module.h"
#include "scripting/rendering-module.h"
#include "scripting/samplers-module.h"
#include "scripting/pipeline-module.h"
#include "scripting/animation-module.h"
#include "easylogging++.h"
#include "chaiscript/chaiscript.hpp"
#include "chaiscript/math.hpp"
#include <iostream>

using namespace raytracer::scripting;
using namespace chaiscript;


namespace raytracer
{
    namespace scripting
    {
        // Must be in raytracer::scripting for testing purposes
        void create_modules(chaiscript::ChaiScript& chai)
        {
            using namespace raytracer::scripting::_private_;

            chai.add(create_imaging_module());
            chai.add(create_math_module());
            chai.add(create_primitives_module());
            chai.add(create_cameras_module());
            chai.add(create_lights_module());
            chai.add(create_raytracing_module());
            chai.add(create_materials_module());
            chai.add(create_rendering_module());
            chai.add(create_samplers_module());
            chai.add(create_pipeline_module());
            chai.add(create_animation_module());
            chai.add(create_patterns_module());
            chai.add(chaiscript::extras::math::bootstrap());
        }
    }
}

namespace
{
    std::shared_ptr<ChaiScript> initialize_chai()
    {
        auto chai = std::make_shared<ChaiScript>();

        create_modules(*chai);

        return chai;
    }

    void report_error(const chaiscript::exception::eval_error& e)
    {
        LOG(ERROR) << "Error occurred while evaluating script" << std::endl << e.pretty_print() << std::endl;

        if (!e.call_stack.empty())
        {
            auto location = e.call_stack[0].location.start.line;

            CLOG(ERROR, "studio") << "Error on line " << location;
            CLOG(ERROR, "studio") << e.reason;
        }
        else
        {
            CLOG(ERROR, "studio") << e.reason;
        }
    }

    bool file_exists(const std::string& path)
    {
        std::ifstream file(path);

        return file.good();
    }
}


void raytracer::scripting::run_script(const std::string& path)
{
    auto chai = initialize_chai();

    if (!file_exists(path))
    {
        LOG(ERROR) << "File " << path << " does not exist!" << std::endl;
        abort();
    }

    try
    {
        chai->eval_file(path);
    }
    catch (const chaiscript::exception::eval_error& e)
    {
        report_error(e);
        abort();
    }
}

void raytracer::scripting::run(const std::string& source)
{
    auto chai = initialize_chai();

    try
    {
        chai->eval(source);
    }
    catch (const chaiscript::exception::eval_error& e)
    {
        report_error(e);
        abort();
    }
}

#endif
