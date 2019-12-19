
#include "app.h"

#include "plane/plane.h"

void App::Init(void) {
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	GLint viewport_size[4];
	glGetIntegerv(GL_VIEWPORT, viewport_size);
	viewport_width_ = viewport_size[2];
	viewport_height_ = viewport_size[3];

	plane_ = glshape::plane::Create(2, 2);

	fragment_shader_ = gl::ShaderPtr(new gl::Shader(GL_FRAGMENT_SHADER));
	fragment_shader_->load_file(root_dir_ + "/shader/fragment.glsl");

	vertex_shader_ = gl::ShaderPtr(new gl::Shader(GL_VERTEX_SHADER));
	vertex_shader_->load_file(root_dir_ + "/shader/vertex.glsl");

	shader_program_ = gl::ShaderProgramPtr(new gl::ShaderProgram);

	shader_program_->Attach(*vertex_shader_);
	shader_program_->Attach(*fragment_shader_);
	shader_program_->Link();
	shader_program_->GetUniforms();

}

void App::Draw(void) {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, buffers);

	animation_time_ += 0.001f;

	shader_program_->Use();

	shader_program_->SetUniform("time", animation_time_);

	shader_program_->SetUniform("resolution", glm::value_ptr( glm::vec2(viewport_width_, viewport_height_) ));

	plane_->Draw();
	
}
