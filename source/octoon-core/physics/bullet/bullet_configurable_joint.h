#ifndef OCTOON_BULLET_CONFIGURABLE_JOINT_H_
#define OCTOON_BULLET_CONFIGURABLE_JOINT_H_

#include <memory>

#include <octoon/runtime/platform.h>
#include <octoon/math/math.h>

#include <octoon/physics/physics_context.h>
#include <octoon/physics/physics_configurable_joint.h>

#include "bullet_joint.h"
#include "bullet_type.h"

namespace octoon
{
	namespace physics
	{
		class OCTOON_EXPORT BulletConfigurableJoint : public PhysicsConfigurableJoint, public BulletJoint
		{
		public:
			BulletConfigurableJoint() noexcept;
			virtual ~BulletConfigurableJoint() noexcept;

			virtual void connect(std::shared_ptr<PhysicsRigidbody> lhs, std::shared_ptr<PhysicsRigidbody> rhs) override;

			virtual void setRigidATransform(const math::float3& position, const math::Quaternion& rotation) noexcept;
			virtual void setRigidBTransform(const math::float3& position, const math::Quaternion& rotation) noexcept;

			virtual void setXMotion(ConfigurableJointMotion motion) override;
			virtual void setYMotion(ConfigurableJointMotion motion) override;
			virtual void setZMotion(ConfigurableJointMotion motion) override;

			virtual void setAngularXMotion(ConfigurableJointMotion motion) override;
			virtual void setAngularYMotion(ConfigurableJointMotion motion) override;
			virtual void setAngularZMotion(ConfigurableJointMotion motion) override;

			virtual ConfigurableJointMotion getXMotion() override;
			virtual ConfigurableJointMotion getYMotion() override;
			virtual ConfigurableJointMotion getZMotion() override;

			virtual ConfigurableJointMotion getAngularXMotion() override;
			virtual ConfigurableJointMotion getAngularYMotion() override;
			virtual ConfigurableJointMotion getAngularZMotion() override;

			virtual void setLowXLimit(float limit);
			virtual void setLowYLimit(float limit);
			virtual void setLowZLimit(float limit);

			virtual void setHighXLimit(float limit);
			virtual void setHighYLimit(float limit);
			virtual void setHighZLimit(float limit);

			virtual void setDistanceLimit(float distance);
			virtual void setTwistLimit(float min, float max);
			virtual void setSwingLimit(float limit_y, float limit_z);
			virtual void setPyramidSwingLimit(float min_y, float max_y, float min_z, float max_z);

			virtual void setDriveMotionX(float motion);
			virtual void setDriveMotionY(float motion);
			virtual void setDriveMotionZ(float motion);

			virtual void setDriveAngularX(float motion);
			virtual void setDriveAngularY(float motion);
			virtual void setDriveAngularZ(float motion);


		private:
			BulletConfigurableJoint(const BulletConfigurableJoint&) = delete;
			BulletConfigurableJoint& operator=(const BulletConfigurableJoint&) = delete;

		private:
			BulletContext* context_;
			std::unique_ptr<btGeneric6DofSpringConstraint> _joint;
		};
	}
}

#endif