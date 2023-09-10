/*
 * description:
 * author@elecfrog
 */
#pragma once

// avoid statement exposition

// shpae - circle, sqaure
// renderer -- raster vector 


struct Renderer
{
    virtual void RenderCircle(float ...) = 0;
    
};

struct Vector : Renderer
{
    virtual void RenderCircle(float ...) override
    {
        ./....
    }
};

struct Rasteruzer : Renderer
{
    virtual void RenderCircle(float ...) override
    {
        ./....
    }
};

struct Shape
{
protected:
    Renderer& renderer;
    Shape(Renderer& renderer) : renderer(renderer) 
    {
        
    }

public:
    virtual void Draw() = 0;
    virtual void Resize(float factor) = 0;
    
};

struct Circle : Shape
{
    Circle(Renderer& renderer, float x, float y, float raius) 
    : Shape(renderer) , .. . 
    {}

    float ,x , y , raius;
    
    
    // impl
};


