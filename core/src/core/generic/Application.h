#pragma once

#include "core/_Core.h"
#include "utility.h"

namespace core {

	class CORE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	};
	
	//defined by client
	Application* createApplication();
}

