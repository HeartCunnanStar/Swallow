#pragma once

#include "Swallow/Core.h"
#include "Layer.h"

#include <vector>

namespace Swallow {

	class SWALLOW_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlayer(Layer* overlayer);
		void PopLayer(Layer* layer);
		void PopOverlayer(Layer* overlayer);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }

	private:
		std::vector<Layer*> m_layers;
		unsigned int m_layer_insert_idx = 0;
	};

}