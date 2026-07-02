//
// Created by jay on 7/2/26.
//

#ifndef JSB_GRAPHICSOBSERVER_H
#define JSB_GRAPHICSOBSERVER_H

#endif //JSB_GRAPHICSOBSERVER_H

typedef struct graphicsData {
    int posit;
} GraphicsData;

/**
 * Defines an interface
 */
class GraphicsObserver {
public:
    virtual ~GraphicsObserver() = default;
    virtual void updateGraphics();
};