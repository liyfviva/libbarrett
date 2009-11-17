/*
 * wam.h
 *
 *  Created on: Sep 25, 2009
 *      Author: dc
 */

#ifndef WAM_H_
#define WAM_H_


#include <map>

#include <barrett/wam/wam.h>
#include <barrett/wam/wam_local.h>

#include "./detail/ca_macro.h"
#include "./units.h"
#include "./systems/abstract/system.h"


namespace barrett {


template<size_t DOF>
class Wam : public systems::System {
public:
	typedef units::JointTorques<DOF> jt_type;
	typedef units::JointPositions<DOF> jp_type;
	typedef units::JointVelocities<DOF> jv_type;


// IO
public:		Input<jt_type> input;
public:		Output<jp_type> jpOutput;
protected:	typename Output<jp_type>::Value* jpOutputValue;
public:		Output<jv_type> jvOutput;
protected:	typename Output<jv_type>::Value* jvOutputValue;


public:
	Wam();
	virtual ~Wam();

	jp_type getJointPositions();
	jv_type getJointVelocities();

	void gravityCompensate(bool compensate = true);
	void moveHome();
	bool moveIsDone();
	void idle();

	static int handleCallback(struct bt_wam_local* wamLocal);

	int operateCount;

protected:
	struct bt_wam* wam;
	struct bt_wam_local* wamLocal;

	virtual void readSensors();
	virtual void operate();


	static std::map<struct bt_wam_local*, Wam<DOF>*> activeWams;

private:
	DISALLOW_COPY_AND_ASSIGN(Wam);
};


}


// include template definitions
#include "./detail/wam-inl.h"


#endif /* WAM_H_ */
