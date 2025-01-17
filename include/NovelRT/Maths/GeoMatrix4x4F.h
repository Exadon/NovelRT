// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_GEOMATRIX4_H
#define NOVELRT_MATHS_GEOMATRIX4_H

#include "GeoVector4F.h"

namespace NovelRT::Maths
{
    class GeoMatrix4x4F
    {
        friend class Graphics::RenderObject;
        friend class Graphics::ImageRect;
        friend class Graphics::BasicFillRect;
        friend class Graphics::TextRect;
        friend class Graphics::RenderingService;
        friend class Graphics::Camera;

    private:
        explicit GeoMatrix4x4F(glm::mat4 matrix) noexcept
            : x(*reinterpret_cast<GeoVector4F*>(&matrix[0])),
              y(*reinterpret_cast<GeoVector4F*>(&matrix[1])),
              z(*reinterpret_cast<GeoVector4F*>(&matrix[2])),
              w(*reinterpret_cast<GeoVector4F*>(&matrix[3]))
        {
        }

    public:
        GeoVector4F x;
        GeoVector4F y;
        GeoVector4F z;
        GeoVector4F w;

        GeoMatrix4x4F() noexcept
            : x(GeoVector4F::zero()), y(GeoVector4F::zero()), z(GeoVector4F::zero()), w(GeoVector4F::zero())
        {
        }

        GeoMatrix4x4F(GeoVector4F x, GeoVector4F y, GeoVector4F z, GeoVector4F w) noexcept : x(x), y(y), z(z), w(w)
        {
        }

        inline bool operator==(GeoMatrix4x4F other) const noexcept
        {
            return *reinterpret_cast<const glm::mat4*>(this) == *reinterpret_cast<const glm::mat4*>(&other);
        }

        inline bool operator!=(GeoMatrix4x4F other) const noexcept
        {
            return *reinterpret_cast<const glm::mat4*>(this) != *reinterpret_cast<const glm::mat4*>(&other);
        }

        inline GeoMatrix4x4F operator+(GeoMatrix4x4F other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) +
                                 *reinterpret_cast<const glm::mat4*>(&other));
        }

        inline GeoMatrix4x4F operator-(GeoMatrix4x4F other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) -
                                 *reinterpret_cast<const glm::mat4*>(&other));
        }

        inline GeoMatrix4x4F operator*(GeoMatrix4x4F other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) *
                                 *reinterpret_cast<const glm::mat4*>(&other));
        }

        inline GeoMatrix4x4F operator+=(GeoMatrix4x4F other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) += *reinterpret_cast<const glm::mat4*>(&other);
            return *this;
        }

        inline GeoMatrix4x4F operator-=(GeoMatrix4x4F other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) -= *reinterpret_cast<const glm::mat4*>(&other);
            return *this;
        }

        inline GeoMatrix4x4F operator*=(GeoMatrix4x4F other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) *= *reinterpret_cast<const glm::mat4*>(&other);
            return *this;
        }

        inline GeoMatrix4x4F operator+(float other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) + other);
        }

        inline GeoMatrix4x4F operator-(float other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) - other);
        }

        inline GeoMatrix4x4F operator*(float other) const noexcept
        {
            return GeoMatrix4x4F(*reinterpret_cast<const glm::mat4*>(this) * other);
        }

        inline GeoMatrix4x4F operator+=(float other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) += other;
            return *this;
        }

        inline GeoMatrix4x4F operator-=(float other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) -= other;
            return *this;
        }

        inline GeoMatrix4x4F operator*=(float other) noexcept
        {
            *reinterpret_cast<glm::mat4*>(this) *= other;
            return *this;
        }

        static GeoMatrix4x4F getDefaultIdentity() noexcept
        {
            return GeoMatrix4x4F(glm::identity<glm::mat4>());
        }
    };
}

#endif // NOVELRT_MATHS_GEOMATRIX4_H
