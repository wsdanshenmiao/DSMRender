#pragma once
#ifndef __GAMEOBJECT__H__
#define __GAMEOBJECT__H__

#include <memory>
#include "Model.h"
#include "Transform.h"
#include "../Rendering/Shader/IShader.h"

namespace DSM {

	class GameObject
	{
	public:
		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject&) = default;
		GameObject(GameObject&&) = default;
		GameObject& operator=(const GameObject&) = default;
		GameObject& operator=(GameObject&&) = default;

		void setModel(std::unique_ptr<Model>&& pModel) noexcept;
		const std::unique_ptr<Model>& getModel() const noexcept;
		void setShader(std::unique_ptr<Rendering::IShader>&& pShader) noexcept;
		const std::unique_ptr<Rendering::IShader>& getShader() const noexcept;

		Transform& getTransform() noexcept;
		const Transform& getTransform() const noexcept;

	private:
		std::unique_ptr<Model> m_pModel = nullptr;
		std::unique_ptr<Rendering::IShader> m_Shader;
		Transform m_Transform{};
	};
}

#endif // !__GAMEOBJECT__H__
