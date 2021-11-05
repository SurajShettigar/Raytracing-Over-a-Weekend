#ifndef IMAGE_H
#define IMAGE_H

namespace raytracer
{
    class Image
    {
    private:
        float m_aspectRatio = 16.0 / 9.0;
        int m_width = 1280;
        int m_height = 1.125;
        int m_samplesPerPixel = 16;

    public:
        const float &aspectRatio = m_aspectRatio;
        const int &width = m_width;
        const int &height = m_height;
        int& samplesPerPixel = m_samplesPerPixel;

        Image(int width, int height)
            : m_aspectRatio{static_cast<float>(width) / static_cast<float>(height)}, m_width{width}, m_height{height} {}
    };
}

#endif