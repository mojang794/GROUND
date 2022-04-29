#pragma once

namespace gr
{
	class States
	{
	public:
		virtual void init() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;
		virtual void AfterDraw(){}

		virtual void destroyGL() = 0;

		virtual void Pause() {}
		virtual void Resume() {}
	};
}