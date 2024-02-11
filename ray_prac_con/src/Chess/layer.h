#pragma once

#include <vector>
#include <string>
#include "events.h"


// Event Listener / observer of events/
class Layer {
    public:
        Layer(const std::string& name);
        virtual ~Layer() {}

        virtual void Render();
        virtual void OnEvent(Event& event);

        inline const std::string &GetName() const { return debugName; }
    private:
        std::string debugName;
};

// Event handler  
class LayerManager {
    public:
        LayerManager() = default;
        ~LayerManager() ;

        void addLayer(Layer* layer);
        void renderLayers();
        void handleEvent(Event& event);

    private: 
        std::vector<Layer*> layers;
};
