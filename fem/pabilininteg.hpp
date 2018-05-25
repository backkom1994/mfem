// Copyright (c) 2010, Lawrence Livermore National Security, LLC. Produced at
// the Lawrence Livermore National Laboratory. LLNL-CODE-443211. All Rights
// reserved. See file COPYRIGHT for details.
//
// This file is part of the MFEM library. For more information and source code
// availability see http://mfem.org.
//
// MFEM is free software; you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License (as published by the Free
// Software Foundation) version 2.1 dated February 1999.

#ifndef MFEM_PA_BILINEARINTEG
#define MFEM_PA_BILINEARINTEG

#include "bilininteg.hpp"
#include "fespace.hpp"

namespace mfem {

class PAIntegrator : public BilinearFormIntegrator
{
    protected:
    Coefficient *Q;
    FiniteElementSpace *fes;
    const FiniteElement *fe;
    const TensorBasisElement *tfe;
    const IntegrationRule *ir;
    Array<int> tDofMap;
    int GeomType;
    int FEOrder;
    bool onGPU;
    bool hasTensorBasis;
    int nDim;
    int nElem;
    int nDof;
    int nQuad;

    public:
    PAIntegrator(Coefficient &q, FiniteElementSpace &f, bool gpu);
    virtual bool PAIsEnabled() const {return true;}
    int GetExpandedNDOF() {return nElem*nDof;}
    FiniteElementSpace *GetFES() {return fes;}
    virtual ~PAIntegrator();
    virtual void BatchedPartialAssemble() = 0;
    virtual void BatchedAssembleElementMatrices(DenseTensor &elmats) = 0;
    virtual void PAMult(const Vector &x, Vector &y) = 0;
};

}

#endif