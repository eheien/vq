// Copyright (c) 2012-2014 Eric M. Heien, Michael K. Sachs, John B. Rundle
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include "QuakeLib.h"

#include <map>

#ifndef _BLOCK_H_
#define _BLOCK_H_

#define GREEN_VAL       double

typedef unsigned int BlockID;
typedef unsigned int FaultID;
typedef unsigned int SectionID;

struct StateCheckpointData {
    double      slipDeficit;
    double      cff;
    double      shear_stress;
    double      normal_stress;
    double      updateField;
};

typedef struct StateCheckpointData StateCheckpointData;

typedef std::map<BlockID, StateCheckpointData> CheckpointSet;

struct BlockVal {
    double      val;
    BlockID     block_id;
};

typedef struct BlockVal BlockVal;

enum BlockValOp {
    BLOCK_VAL_UNDEFINED,
    BLOCK_VAL_MIN,          // Get the minimum value and associated block
    BLOCK_VAL_MAX,          // Get the maximum value and associated block
    BLOCK_VAL_SUM,          // Get the sum over all blocks
};

struct BlockSweepVals {
    double          slip, init_shear, init_normal, final_shear, final_normal;
    unsigned int    sweep_num;
    BlockID         element_id;
};

typedef struct BlockSweepVals BlockSweepVals;

std::ostream &operator<<(std::ostream &os, const BlockVal &bv);

/*!
 Class of block attributes. These attributes are static during the simulation except rand.
*/
class Block : public quakelib::SimElement {
    private:
        BlockID         id;                 // block id
        FaultID         fid;                // fault id
        SectionID       sid;                // section id

        // constants during simulation
        double          dynamic_val;        // dynamic failure value for this block

        double          init_shear_stress;  // initial shear stress
        double          init_normal_stress; // initial normal stress

        bool            failed;

    public:

        void get_rake_and_normal_stress_due_to_block(double stresses[2], const double &sample_dist, const Block &source_block) const;

        //! Resets the values of this block.
        void clear(void);

        bool getFailed(void) const {
            return failed;
        };
        void setFailed(bool in_failed) {
            failed = in_failed;
        };

        // Functions for manipulation of block parameters
        //! Set the block ID of this block.
        void setBlockID(const BlockID &new_id) {
            id = new_id;
        };
        //! Return the block ID of this block.
        BlockID getBlockID(void) const {
            return id;
        };

        //! Set the fault ID of this block.
        void setFaultID(const FaultID &new_fid) {
            fid = new_fid;
        };
        //! Return the fault ID of this block.
        FaultID getFaultID(void) const {
            return fid;
        };

        //! Set the section ID of this block.
        void setSectionID(const SectionID &new_sid) {
            sid = new_sid;
        };
        //! Return the section ID of this block.
        SectionID getSectionID(void) const {
            return sid;
        };

        //! Get the dynamic triggering value for this block.
        double getDynamicVal(void) const {
            return dynamic_val;
        };
        //! Set the dynamic triggering value for this block.
        void setDynamicVal(const double &new_dyn_val) {
            dynamic_val = new_dyn_val;
        };

        //! Set the initial shear stress of this block in bars.
        void setInitShearStress(const double &new_stress) {
            init_shear_stress = new_stress;
        };
        //! Get the initial shear stress of this block in bars.
        double getInitShearStress(void) const {
            return init_shear_stress;
        };
        //! Set the initial normal stress of this block in bars.
        void setInitNormalStress(const double &new_stress) {
            init_normal_stress = new_stress;
        };
        //! Get the initial normal stress of this block in bars.
        double getInitNormalStress(void) const {
            return init_normal_stress;
        };
};

typedef std::vector<Block> BlockList;
typedef std::vector<BlockID> BlockIDList;
typedef std::map<BlockID, int> BlockIDMap;

std::ostream &operator<<(std::ostream &os, const Block &b);

#endif
