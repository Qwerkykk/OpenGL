#pragma once


struct Mouse
{
public:
	static Mouse& instance()
	{
		static Mouse* instance = new Mouse();
		return *instance;
	}

	double lastX, lastY;
	bool firstMouse;

	Mouse(Mouse const&) = delete;
	void operator=(Mouse const&) = delete;

private:
	Mouse(): lastX(400), lastY(300), firstMouse(true)
	{
	};
	~Mouse();
};
