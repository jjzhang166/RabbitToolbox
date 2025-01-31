#include <octoon/box_collider_component.h>
#include <octoon/physics_feature.h>

namespace octoon
{
	OctoonImplementSubClass(BoxColliderComponent, ColliderComponent, "BoxColliderComponent")

	BoxColliderComponent::BoxColliderComponent() noexcept
		: size_(math::float3::One)
		, center_(math::float3::Zero)
		, rotation_(math::Quaternion::Zero)
		, contactOffset_(0.04f)
		, restOffset_(0.0f)
		, needUpdatePose_(false)
		, localPose_(math::float4x4::One)
	{
    }

	BoxColliderComponent::BoxColliderComponent(const math::float3& size, float contactOffset, float restOffset) noexcept
		: size_(size)
		, center_(math::float3::Zero)
		, rotation_(math::Quaternion::Zero)
		, contactOffset_(contactOffset)
		, restOffset_(restOffset)
		, needUpdatePose_(false)
		, localPose_(math::float4x4::One)
	{
		assert(contactOffset > restOffset);
	}

	BoxColliderComponent::BoxColliderComponent(float width, float height, float depth) noexcept
		: size_(math::float3(width, height, depth))
		, center_(math::float3::Zero)
		, rotation_(math::Quaternion::Zero)
		, contactOffset_(0.04f)
		, restOffset_(0.0f)
		, needUpdatePose_(false)
		, localPose_(math::float4x4::One)
	{
	}

	BoxColliderComponent::BoxColliderComponent(float x, float y, float z, float contactOffset, float restOffset) noexcept
		: size_(math::float3(x, y, z))
		, center_(math::float3::Zero)
		, rotation_(math::Quaternion::Zero)
		, contactOffset_(contactOffset)
		, restOffset_(restOffset)
		, needUpdatePose_(false)
		, localPose_(math::float4x4::One)
	{
		assert(contactOffset > restOffset);
	}

    BoxColliderComponent::~BoxColliderComponent()
    {
    }

	void
	BoxColliderComponent::setWidth(float width) noexcept
	{
		if (shape_)
			shape_->setWidth(width);
		this->size_.x = width;
	}

	void 
	BoxColliderComponent::setHeight(float height) noexcept
	{
		if (shape_)
			shape_->setHeight(height);
		this->size_.y = height;
	}

	void
	BoxColliderComponent::setDepth(float depth) noexcept
	{
		if (shape_)
			shape_->setDepth(depth);
		this->size_.z = depth;
	}

	void
	BoxColliderComponent::setSize(const math::float3& sz) noexcept
	{
		if (shape_)
		{
			shape_->setWidth(size_.x);
			shape_->setHeight(size_.y);
			shape_->setDepth(size_.z);
		}
		this->size_ = sz;
	}

	void
	BoxColliderComponent::setCenter(const math::float3& center) noexcept
	{
		if (this->center_ != center)
		{
			if (shape_)
				shape_->setCenter(center);

			this->center_ = center;
			this->needUpdatePose_ = true;
		}
	}

	void
	BoxColliderComponent::setQuaternion(const math::Quaternion& rotation) noexcept
	{
		if (this->rotation_ != rotation)
		{
			if (shape_)
				shape_->setQuaternion(rotation);

			this->rotation_ = rotation;
			this->needUpdatePose_ = true;
		}
	}

	const math::float3&
	BoxColliderComponent::getSize() const noexcept
	{
		return this->size_;
	}

	float
	BoxColliderComponent::getWidth() const noexcept
	{
		return this->size_.x;
	}

	float
	BoxColliderComponent::getHeight() const noexcept
	{
		return this->size_.y;
	}

	float
	BoxColliderComponent::getDepth() const noexcept
	{
		return this->size_.z;
	}

	const math::float3& 
	BoxColliderComponent::getCenter() const noexcept
	{
		return this->center_;
	}

	const math::Quaternion&
	BoxColliderComponent::getQuaternion() const noexcept
	{
		return this->rotation_;
	}

	const math::float4x4&
	BoxColliderComponent::getLocalPose() const noexcept
	{
		if (needUpdatePose_)
		{
			localPose_.makeRotation(this->rotation_, this->center_);
			needUpdatePose_ = false;
		}

		return localPose_;
	}

	void
	BoxColliderComponent::setContactOffset(float offset) noexcept
	{
		if (shape_)
			shape_->setContactOffset(offset);
		this->contactOffset_ = shape_->getContactOffset();
	}

	float
	BoxColliderComponent::getContactOffset() const noexcept
	{
		return this->contactOffset_;
	}

	void
	BoxColliderComponent::setRestOffset(float offset) noexcept
	{
		if (shape_)
			shape_->setRestOffset(offset);
		this->restOffset_ = shape_->getRestOffset();
	}

	float
	BoxColliderComponent::getRestOffset() const noexcept
	{
		return this->restOffset_;
	}

    GameComponentPtr
	BoxColliderComponent::clone() const noexcept
    {
		auto instance = std::make_shared<BoxColliderComponent>();
		instance->setName(this->getName());
		instance->setWidth(this->getWidth());
		instance->setHeight(this->getHeight());
		instance->setDepth(this->getDepth());
		instance->setCenter(this->getCenter());
		return instance;
    }

	std::shared_ptr<PhysicsShape>
	BoxColliderComponent::getShape() noexcept
	{
		return this->shape_;
	}

    void
	BoxColliderComponent::onActivate() except
    {
		auto physicsFeature = this->getFeature<PhysicsFeature>();
		if (physicsFeature)
		{
			PhysicsBoxShapeDesc boxDesc;
			boxDesc.width = size_.x;
			boxDesc.height = size_.y;
			boxDesc.depth = size_.z;
			shape_ = physicsFeature->getContext()->createBoxShape(boxDesc);
			shape_->setCenter(this->getCenter());
			shape_->setQuaternion(this->getQuaternion());
			shape_->setContactOffset(this->contactOffset_);
			shape_->setRestOffset(this->restOffset_);

			this->center_ = shape_->getCenter();
			this->rotation_ = shape_->getQuaternion();
			this->restOffset_ = shape_->getRestOffset();
			this->contactOffset_ = shape_->getContactOffset();
		}
	}

    void
	BoxColliderComponent::onDeactivate() noexcept
    {
		shape_.reset();
		shape_ = nullptr;
    }
}