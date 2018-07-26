#include "main_controller.h"

#include "controllers/main_menu.h"
#include "controllers/asset_window.h"
#include "controllers/camera_window.h"
#include "controllers/hierarchy_window.h"
#include "controllers/inspector_window.h"
#include "controllers/message_window.h"
#include "controllers/theme_manager.h"
#include "controllers/about_window.h"

#include <octoon/octoon.h>

namespace octoon
{
	namespace editor
	{
		OctoonImplementSubClass(MainController, GameComponent, "MainController")

		MainController::MainController() noexcept
		{
		}

		MainController::~MainController() noexcept
		{
		}

		void
		MainController::onActivate() noexcept
		{
			main_ = GameObject::create("MainView");
			main_->addComponent<MainMenu>();
			main_->addComponent<CameraWindow>();
			main_->addComponent<AssetWindow>();
			main_->addComponent<HierarchyWindow>();
			main_->addComponent<InspectorWindow>();
			main_->addComponent<ThemeManager>();
			main_->addComponent<MessageWindow>();
			main_->addComponent<AboutWindow>();
			main_->addMessageListener("editor:menu:file:exit", [](const runtime::any&) { std::exit(0); });

			auto text = model::makeTextContours(L"Octoon Studio", { "../../system/fonts/DroidSansFallback.ttf", 24 });
			auto aabb = model::aabb(text);

			for (auto& it : text)
				*it -= aabb.center();

			auto material = std::make_shared<video::TextMaterial>();
			material->setLean(0.0f);
			material->setTextColor(video::TextColor::FrontColor, math::float3(180.0, 180.0, 180.0) / 255.0f);
			material->setTextColor(video::TextColor::SideColor, math::float3(125.f, 125.f, 125.f) / 255.0f);

			object_ = GameObject::create("Text");
			object_->addComponent<MeshFilterComponent>(model::makeMesh(text));
			object_->addComponent<MeshRendererComponent>(material);
		}

		void
		MainController::onDeactivate() noexcept
		{
			main_.reset();
			object_.reset();
		}

		GameComponentPtr 
		MainController::clone() const noexcept
		{
			return std::make_shared<MainController>();
		}
	}
}