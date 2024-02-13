#include "layer.h"
#include <iostream>

// Layer section
Layer::Layer(const std::string& name) : debugName(name) {}

void Layer::Render() {
    std::cout << "Layer: Render from base Layer" << std::endl;
}

void Layer::OnEvent( Event& event) {
    std::cout << "Layer: Event handled by base layer" << std::endl;
}
///////


// Layer Manager Section
LayerManager::~LayerManager() {
    for (auto layer: layers) {
        delete layer;
    }
}
void LayerManager::renderLayers() {
    for(auto layer: layers) {
       (*layer).Render(); 
    }
}

void LayerManager::addLayer(Layer* layer) {
    layers.push_back(layer);
}

void LayerManager::handleEvent(Event& event) {
    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        (*it)->OnEvent(event);
        if(event.m_Handled) {
            return;
        }
    }

}
////////



