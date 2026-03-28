#ifndef ENGINEUI_HPP
#define ENGINEUI_HPP

#include "EditorState.hpp"
#include <filesystem>
#include <unordered_map>
#include "Pengu_Engine/Graphics/Texture.hpp"

namespace fs = std::filesystem;

struct GLFWwindow;
namespace Pengu::Core { class PenguEngine; }

inline constexpr const char* PAYLOAD_TEXTURE = "TEXTURE_ASSET";

struct TextureDragPayload
{
	char path[256];
};

inline constexpr const char* PAYLOAD_MESH = "MESH_ASSET";

struct MeshDragPayload
{
	char path[256];
};

class EngineUI {
public:

	void init(GLFWwindow* window, Pengu::Core::PenguEngine* engine);

	void render(EditorState& state);

	void shutdown();

private:
	Pengu::Core::PenguEngine* m_engine = nullptr;

	void drawMenuBar(EditorState& state);

	void drawHierarchy(EditorState& state);
	void drawInspector(EditorState& state);

	void drawProfiler(EditorState& state);

	void drawContentBrowser(EditorState& state);
	unsigned int getIconForEntry(const fs::directory_entry& entry);
	void loadIcons();

	fs::path m_rootPath = "../assets";
	fs::path m_currentPath = "../assets";
	float m_thumbnailSize = 80.0f;

	std::unordered_map<std::string, std::shared_ptr<Pengu::Graphics::Texture>> m_icons;
};

#endif // !ENGINEUI_HPP
