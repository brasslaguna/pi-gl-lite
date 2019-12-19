
#include "app.h"

#include "plane/plane.h"

void App::Init(void) {
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	plane_ = glshape::plane::Create(2, 2);

	auto fragment_shader_ = shader(new gl::Shader(GL_FRAGMENT_SHADER));
	fragment_shader_->load_file(root_dir_ + "/shader/fragment.glsl");

	auto vertex_shader_ = shader(new gl::Shader(GL_VERTEX_SHADER));
	vertex_shader_->load_file(root_dir_ + "/shader/vertex.glsl");

	auto shader_program_ = shader_program(new gl::ShaderProgram);

	shader_program_->Attach(*vertex_shader_);
	shader_program_->Attach(*fragment_shader_);
	shader_program_->Link();
	shader_program_->GetUniforms();

}

void App::Draw(void) {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glClearColor(0, 0.5f, 1.0f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, buffers);

	shader_program_->Use();

	plane_->Draw();
	
}
