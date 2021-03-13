#pragma once
#include "Camera.h"

class CameraController
{
public:
	static CameraController& instance()
	{
		static CameraController* instance = new CameraController();
		return *instance;
	}

	inline void Bind(Camera& camera) { m_Camera = &camera; }
	inline void Unbind() { m_Camera = nullptr; }
	inline Camera& GetCamera() { return *m_Camera; }

	CameraController(CameraController const&) = delete;
	void operator=(CameraController const&) = delete;

private:
	~CameraController()
	{
	};

	CameraController()
	{
	};

	 Camera* m_Camera;
};
