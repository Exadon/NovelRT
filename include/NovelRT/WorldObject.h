// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_WORLDOBJECT_H
#define NOVELRT_WORLDOBJECT_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

namespace NovelRT
{
    /**
     * @brief Represents an object in the game world.
     *
     * WorldObjects have a transform, and can be active or not.
     * They are also rendered in the world in order of their layer.
     */
    class WorldObject
    {
    private:
        Transform _transform;
        int32_t _layer;
        bool _active;

    protected:
        bool _isDirty;

    public:
        WorldObject(Transform transform, int32_t layer) noexcept;
        virtual ~WorldObject()
        {
        }

        inline Transform& transform() noexcept
        {
            _isDirty = true;
            return _transform;
        }

        inline const Transform& transform() const noexcept
        {
            return _transform;
        }

        inline const int32_t& layer() const noexcept
        {
            return _layer;
        }

        inline int32_t& layer() noexcept
        {
            return _layer;
        }

        virtual bool getActive() const noexcept;

        virtual void setActive(bool value) noexcept;

        virtual void executeObjectBehaviour() = 0;
    };
}

#endif // NOVELRT_WORLDOBJECT_H
