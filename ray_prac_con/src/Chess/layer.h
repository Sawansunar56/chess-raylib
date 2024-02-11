#pragma once

#include <vector>
#include <string>
#include "events.h"

class EventListener  {
    public:
        virtual void OnEvent(Event& event) = 0;
};

class Layer : public EventListener {
    public:
        Layer(const std::string& name);
        virtual ~Layer() {}

        virtual void Render();
        virtual void OnEvent(Event& event) override;

        inline const std::string &GetName() const { return debugName; }
    private:
        std::string debugName;
};

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
