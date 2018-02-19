﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <atomic>
# include <ThirdParty/Box2D/Box2D.h>
# include "Fwd.hpp"
# include "Optional.hpp"
# include "Array.hpp"
# include "PointVector.hpp"
# include "Line.hpp"
# include "LineString.hpp"
# include "Circle.hpp"
# include "System.hpp"

namespace s3d
{
	using P2BodyID = uint64;

	struct P2Material
	{
		double density = 1.0;

		double restitution = 0.0;

		double friction = 0.2;

		constexpr P2Material(None_t) {}

		constexpr P2Material(double _density = 1.0, double _restitution = 0.1, double _friction = 0.2)
			: density(_density)
			, restitution(_restitution)
			, friction(_friction) {}
	};

	struct P2Filter
	{
		uint16 categoryBits = 0b0000'0000'0000'0001;

		uint16 maskBits = 0b1111'1111'1111'1111;

		int16 groupIndex = 0;

		constexpr P2Filter(None_t) {}

		constexpr P2Filter(
			uint16 _categoryBits = 0b0000'0000'0000'0001,
			uint16 _maskBits = 0b1111'1111'1111'1111u,
			int16  _groupIndex = 0)
			: categoryBits(_categoryBits)
			, maskBits(_maskBits)
			, groupIndex(_groupIndex) {}
	};

	enum class P2BodyType
	{
		Static,

		Kinematic,

		Dynamic
	};

	enum class P2ShapeType
	{
		Line,

		LineString,

		Circle,

		Rect,

		Triangle,

		Quad,

		Polygon
	};

	class P2World
	{
	private:

		class CP2World;

		std::shared_ptr<CP2World> pImpl;

	public:

		P2World(const Vec2& gravity = Vec2(0.0, 9.8));

		void setSleepEnabled(bool enabled);

		bool getSleepEnabled() const;

		void setGravity(const Vec2& gravity);

		Vec2 getGravity() const;

		void update(double timeStep = System::DeltaTime(), int32 velocityIterations = 6, int32 positionIterations = 2) const;

		P2Body createEmpty(const Vec2& center, P2BodyType bodyType = P2BodyType::Dynamic);

		P2Body createLine(const Vec2& center, const Vec2& begin, const Vec2& end, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		P2Body createLine(const Vec2& center, const Line& line, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		P2Body createLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		P2Body createClosedLineString(const Vec2& center, const LineString& lines, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		P2Body createCircle(const Vec2& center, double r, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		P2Body createCircle(const Vec2& center, double r, const Vec2& offset, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);

		P2Body createCircle(const Vec2& center, const Circle& circle, const P2Material& material = P2Material(), const P2Filter& filter = P2Filter(), P2BodyType bodyType = P2BodyType::Dynamic);


		b2World& getData();
	};

	class P2World::CP2World
	{
	private:

		b2World m_world;

		//ContactListener m_contactListner;

		std::atomic<P2BodyID> m_currentID = 0;

		P2BodyID generateNextID()
		{
			return ++m_currentID;
		}

	public:

		CP2World(const Vec2& gravity);

		void setSleepEnabled(bool enabled);

		bool getSleepEnabled() const;

		void setGravity(const Vec2& gravity);

		Vec2 getGravity() const;

		void update(double timeStep, int32 velocityIterations, int32 positionIterations);

		P2Body createEmpty(P2World& world, const Vec2& center, P2BodyType bodyType);

		P2Body createLine(P2World& world, const Vec2& center, const Line& line, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2Body createLineString(P2World& world, const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2Body createClosedLineString(P2World& world, const Vec2& center, const LineString& lines, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		P2Body createCircle(P2World& world, const Vec2& center, const Circle& circle, const P2Material& material, const P2Filter& filter, P2BodyType bodyType);

		//const Array<PhysicsContact>& getContacts() const;

		b2World& getData()
		{
			return m_world;
		}
	};

	class P2Body
	{
	private:

		class CP2Body;

		std::shared_ptr<CP2Body> pImpl;

		friend class P2World;

		P2Body(P2World& world, P2BodyID id, const Vec2& center, P2BodyType bodyType);

	public:

		P2Body();

		P2BodyID id() const;

		bool isEmpty() const;

		explicit operator bool() const
		{
			return !isEmpty();
		}

		P2Body& addLine(const Line& line, const P2Material& material, const P2Filter& filter);

		P2Body& addLineString(const LineString& lines, const P2Material& material, const P2Filter& filter);

		P2Body& addClosedLineString(const LineString& lines, const P2Material& material, const P2Filter& filter);

		P2Body& addCircle(const Circle& circle, const P2Material& material, const P2Filter& filter);


		//void setSleepingAllowed(bool allowed);

		//bool isSleepingAllowed() const;

		//void setAwake(bool awake);

		//bool isAwake() const;

		//void setPos(double x, double y);

		//void setPos(const Vec2& pos);

		//void moveBy(double x, double y);

		//void moveBy(const Vec2& v);

		//void setAngle(double angle);

		//void rotateBy(double angle);

		//void setTransform(double x, double y, double angle);

		//void setTransform(const Vec2& pos, double angle);

		//void applyForce(const Vec2& force);

		//void applyForce(const Vec2& force, const Vec2& offset);

		//void applyForceAt(const Vec2& force, const Vec2& pos);

		//void applyLinearImpulse(const Vec2& force);

		//void applyLinearImpulse(const Vec2& force, const Vec2& offset);

		//void applyLinearImpulseAt(const Vec2& force, const Vec2& offset);

		//void applyTorque(double torque);

		//void applyAngularImpulse(double torque);

		Vec2 getPos() const;

		double getAngle() const;

		//std::pair<Vec2, double> getTransform() const;

		//void setVelocity(const Vec2& v);

		//Vec2 getVelocity() const;

		//void setAngularVelocity(double omega);

		//double getAngularVelocity() const;

		//void setDamping(double damping);

		//double getDamping() const;

		//void setAngularDamping(double damping);

		//double getAngularDamping() const;

		//void setGravityScale(double scale);

		//double getGravityScale() const;

		//double getMass() const;

		//double getInertia() const;

		//void setBodyType(PhysicsBodyType bodyType);

		//PhysicsBodyType getBodyType() const;

		//void setFixedRotation(bool fixedRotation);

		//bool isFixedRotation() const;

		void draw(const ColorF& color = Palette::White) const;

		//PhysicsShape& shape(size_t index);

		//const PhysicsShape& shape(size_t index) const;

		//template <class PShape, std::enable_if_t<std::is_base_of<PhysicsShape, PShape>::value>* = nullptr>
		//std::shared_ptr<PShape> shapeAs(const size_t index) const;

		//size_t num_shapes() const;
	};

	struct P2Fixture
	{
		Array<b2Fixture*> fixtures;
	};

	class P2Shape
	{
	protected:

		P2Fixture m_fixtures;

	public:

		virtual ~P2Shape() {}

		virtual P2ShapeType getShapeType() const = 0;

		virtual void draw(const ColorF& color) const = 0;

		//void setDensity(double density);

		//double getDensity() const;

		//void setFriction(double friction);

		//double getFriction() const;

		//void setRestitution(double restitution);

		//double getRestitution() const;

		//void setFilter(const P2Filter& filter);

		//P2Filter getFilter() const;
	};

	class P2Line : public P2Shape
	{
	private:

		b2EdgeShape m_shape;

	public:

		P2Line(b2Body& body, const Line& line, const P2Material& material, const P2Filter& filter);

		P2ShapeType getShapeType() const override;

		void draw(const ColorF& color = Palette::White) const override;

		Line getLine() const;
	};

	class P2LineString : public P2Shape
	{
	private:

		b2ChainShape m_shape;

		mutable LineString m_lineString;

		bool m_closed;

	public:

		P2LineString(b2Body& body, const LineString& lines, bool closed, const P2Material& material, const P2Filter& filter);

		P2ShapeType getShapeType() const override;

		void draw(const ColorF& color = Palette::White) const override;

		const LineString& getLineString() const;
	};

	class P2Circle : public P2Shape
	{
	private:

		b2CircleShape m_shape;

	public:

		P2Circle(b2Body& body, const Circle& circle, const P2Material& material, const P2Filter& filter);

		P2ShapeType getShapeType() const override;

		void draw(const ColorF& color = Palette::White) const override;

		Circle getCircle() const;
	};

	class P2Body::CP2Body
	{
	private:

		P2World m_world;

		Array<std::shared_ptr<P2Shape>> m_shapes;

		b2Body* m_body = nullptr;

		P2BodyID m_id = 0;

		//PhysicsBodyInternalData* getInternalData();

	public:

		CP2Body() = default;

		CP2Body(P2World& world, P2BodyID id, const Vec2& center, P2BodyType bodyType);

		~CP2Body();

		P2BodyID id() const;

		void addLine(const Line& line, const P2Material& material, const P2Filter& filter);

		void addLineString(const LineString& lines, bool closed, const P2Material& material, const P2Filter& filter);

		void addCircle(const Circle& circle, const P2Material& material, const P2Filter& filter);

		const b2Body& getBody() const;

		const Array<std::shared_ptr<P2Shape>>& getShapes() const;
	};
}
