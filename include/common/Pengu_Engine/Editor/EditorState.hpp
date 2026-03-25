#ifndef EDITORSTATE_HPP
#define EDITORSTATE_HPP 1

struct EditorState
{
	float viewportWidth = 1280.0f;
	float viewportHeight = 720.0f;

	int selectedEntityID = -1;

	bool  showProfiler = false;
	bool  showInspector = false;
	bool  showHierarchy = false;
	bool  showContentBrowser = false;

	float lastFrameMs = 0.0f;
	float fps = 0.0f;
};

#endif // !EDITORSTATE_HPP
