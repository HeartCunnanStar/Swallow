#include "swpch.h"
#include "LayerStack.h"

namespace Swallow {

	LayerStack::LayerStack()
	{
		m_layer_insert = m_layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_layer_insert = m_layers.emplace(m_layer_insert, layer);
	}

	void LayerStack::PushOverlayer(Layer* overlayer)
	{
		m_layers.emplace_back(overlayer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			m_layer_insert--;
		}
	}

	void LayerStack::PopOverlayer(Layer* overlayer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overlayer);
		if (it != m_layers.end())
			m_layers.erase(it);
	}

}