#include "GameObject.h"

namespace DSM {

	void GameObject::setModel(std::unique_ptr<Model>&& pModel) noexcept
	{
		m_pModel = std::move(pModel);
	}

	const std::unique_ptr<Model>& GameObject::getModel() const noexcept
	{
		return m_pModel;
	}

	void GameObject::setShader(std::unique_ptr<Rendering::IShader>&& pShader) noexcept
	{
		m_Shader = std::move(pShader);
	}

	const std::unique_ptr<Rendering::IShader>& GameObject::getShader() const noexcept
	{
		return m_Shader;
	}

	Transform& GameObject::getTransform() noexcept
	{
		return m_Transform;
	}

	const Transform& GameObject::getTransform() const noexcept
	{
		return m_Transform;
	}

}