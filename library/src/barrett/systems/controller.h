/*
 * controller.h
 *
 *  Created on: Oct 4, 2009
 *      Author: dc
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


#include <list>

#include "abstract/system.h"
#include "abstract/abstract_controller.h"
#include "../detail/ca_macro.h"


namespace Systems {


template<typename InputType, typename OutputType = InputType>
class Controller : public AbstractController {
// IO
public:		Input<InputType> referenceInput;
public:		Input<InputType> feedbackInput;
public:		Output<OutputType> controlOutput;
protected:	typename Output<OutputType>::Value* controlOutputValue;


public:
	Controller() :
		referenceInput(this),
		feedbackInput(this),
		controlOutput(&controlOutputValue) {}
	explicit Controller(const OutputType& initialOutputValue) :
		referenceInput(this),
		feedbackInput(this),
		controlOutput(initialOutputValue, &controlOutputValue) {}

	virtual Input<InputType>* getReferenceInput();
	virtual Input<InputType>* getFeedbackInput();
	virtual Output<OutputType>* getControlOutput();

	virtual void selectAdapter(
			const std::list<JointTorqueAdapter*>& adapters) const
	throw(std::invalid_argument);

protected:
	virtual void operate();

private:
	DISALLOW_COPY_AND_ASSIGN(Controller);
};


}


// include template definitions
#include "./detail/controller-inl.h"


#endif /* CONTROLLER_H_ */
