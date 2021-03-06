/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Yuyu Zhang, Sergey Lisitsyn
 */

#ifndef _NATIVEMULTICLASSMACHINE_H___
#define _NATIVEMULTICLASSMACHINE_H___

#include <shogun/lib/config.h>

#include <shogun/machine/MulticlassMachine.h>

namespace shogun
{

/** @brief experimental abstract native multiclass machine class */
class CNativeMulticlassMachine : public CMulticlassMachine
{
	public:
		/** default constructor  */
		CNativeMulticlassMachine()
		{
		}

		/** destructor */
		virtual ~CNativeMulticlassMachine()
		{
		}

		/** get name */
		virtual const char* get_name() const
		{
			return "NativeMulticlassMachine";
		}

	protected:
		/** init strategy */
		void init_strategy() { }

		/** clear machines */
		void clear_machines() { }

		/** abstract init machine for training method */
		virtual bool init_machine_for_train(CFeatures* data) { return true; }

		/** abstract init machines for applying method */
		virtual bool init_machines_for_apply(CFeatures* data) { return true; }

		/** check whether machine is ready */
		virtual bool is_ready() { return true; }

		/** obtain machine from trained one */
		virtual CMachine* get_machine_from_trained(CMachine* machine) { return NULL; }

		/** get num rhs vectors */
		virtual int32_t get_num_rhs_vectors() { return 0; }

		/** set subset to the features of the machine, deletes old one
		 *
		 * @param subset subset indices to set
		 */
		virtual void add_machine_subset(SGVector<index_t> subset) { }

		/** deletes any subset set to the features of the machine */
		virtual void remove_machine_subset() { }

		/** whether the machine is acceptable in set_machine */
		virtual bool is_acceptable_machine(CMachine *machine) { return true; }

};
}
#endif
