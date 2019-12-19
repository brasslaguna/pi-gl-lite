
#ifndef PI_GL_LITE_APP_H_
#define PI_GL_LITE_APP_H_

#include <string>

#include "shader_program/shader_program.h"
#include "mesh/mesh.h"

class App {

	public:

		App(char** argv) {

			auto exe_name = std::string(argv[0]);
			root_dir_ = exe_name.substr(0, exe_name.find_last_of("\\/")) + "/..";


		};

		void Draw(void);

		void Init(void);

	private:

		gl::ShaderProgramPtr shader_program_;
		gl::ShaderPtr vertex_shader_;
		gl::ShaderPtr fragment_shader_;

		gl::MeshPtr plane_;

		std::string root_dir_;

		float animation_time_ = 0.0f;

		int viewport_height_;
		int viewport_width_;

};

#endif // PI_GL_LITE_APP_H_
