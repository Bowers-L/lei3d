#include "ModelInstance.hpp"

#include "logging/LogGLM.hpp"

namespace lei3d
{
	ModelInstance::ModelInstance(Entity& entity)
		: Component(entity)
	{
	}

	ModelInstance::~ModelInstance()
	{
	}

	void ModelInstance::Init(Model* model)
	{
		m_Model = model;
	}

	void ModelInstance::Draw(Shader* shader, RenderFlag flags, uint32_t bindLocation)
	{
		glm::mat4 model = m_Entity.GetModelMat();
		shader->setUniformMat4("model", model);

		if (m_Model)
		{
			m_Model->Draw(*shader, flags, bindLocation);
		}
	}
} // namespace lei3d