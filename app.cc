
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
	fragment_shader_->load_file(root_dir_ + "/shader/sonar/fragment.glsl");

	vertex_shader_ = gl::ShaderPtr(new gl::Shader(GL_VERTEX_SHADER));
	vertex_shader_->load_file(root_dir_ + "/shader/sonar/vertex.glsl");

	shader_program_ = gl::ShaderProgramPtr(new gl::ShaderProgram);

	shader_program_->Attach(*vertex_shader_);
	shader_program_->Attach(*fragment_shader_);
	shader_program_->Link();
	shader_program_->GetUniforms();


	framebuffer_ = gl::FramebufferPtr(

		new gl::Framebuffer(

			(gl::FramebufferConfig) {

				.width = 256,
				.height = 256

			}

		)

	);

	framebuffer_->CreateBuffer(

		(gl::TextureConfig) {

			.name = "color",
			.target = GL_TEXTURE_2D,
			.internal_format = GL_RGBA,
			.format = GL_RGBA,
			.pixel_type = GL_UNSIGNED_BYTE,

			.parametersi = (gl::TextureParametersi) {

				{ GL_TEXTURE_MAG_FILTER, GL_NEAREST },
				{ GL_TEXTURE_MIN_FILTER, GL_NEAREST },
				{ GL_TEXTURE_WRAP_S, GL_REPEAT },
				{ GL_TEXTURE_WRAP_T, GL_REPEAT }

			}

		}

	);

	framebuffer_->Attach(

		"color",
		GL_TEXTURE_2D,
		GL_COLOR_ATTACHMENT0

	);

	noise_fragment_shader_ = gl::ShaderPtr(new gl::Shader(GL_FRAGMENT_SHADER));
	noise_fragment_shader_->load_file(root_dir_ + "/shader/noise/fragment.glsl");

	noise_vertex_shader_ = gl::ShaderPtr(new gl::Shader(GL_VERTEX_SHADER));
	noise_vertex_shader_->load_file(root_dir_ + "/shader/noise/vertex.glsl");

	noise_shader_program_ = gl::ShaderProgramPtr(new gl::ShaderProgram);

	noise_shader_program_->Attach(*noise_vertex_shader_);
	noise_shader_program_->Attach(*noise_fragment_shader_);
	noise_shader_program_->Link();
	noise_shader_program_->GetUniforms();

	framebuffer_->Bind();
	
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, buffers);

	noise_shader_program_->Use();

	plane_->Draw();

	noise_texture_ = 

		std::static_pointer_cast<gl::Texture>(

			framebuffer_->Get("color", GL_TEXTURE_2D)
		
		);

}

void App::Draw(void) {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, buffers);

	animation_time_ += 0.001f;

	shader_program_->Use();

	shader_program_->SetUniform("animation_time", animation_time_);

	shader_program_->SetUniform("resolution", glm::value_ptr( glm::vec2(viewport_width_, viewport_height_) ));

	noise_texture_->Bind((GLuint)1);

	shader_program_->SetUniform("noise_texture", (GLuint)1);

	plane_->Draw();
	
}
