/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
\*---------------------------------------------------------------------------*/

//- A multiregion solver which computes fluid motion and thermal transport in 
//- fluid zones and only thermal transport in solid zones.
//- Originally based on simpleFoam (most of the capabilities have been kept
//- presumably: MRF, turbulence, ...)
//- Tested (with proper test case) in OF 2006, 2021-01-29 by Victor Pozzobon
//- Associated with article: 
// Sassanis, V., Gamet, L., Rolland, M., Ma, R., & Pozzobon, V. (2020). 
// Numerical determination of the volumetric heat transfer coefficient in fixed beds of wood chips. 
// Chemical Engineering Journal, 128009.

#include "fvCFD.H"
#include "fixedGradientFvPatchFields.H"
#include "regionProperties.H"
#include "singlePhaseTransportModel.H"
#include "turbulentTransportModel.H"
#include "simpleControl.H"
#include "fvOptions.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "addCheckCaseOptions.H"
    #include "setRootCaseLists.H"
    #include "createTime.H"

    regionProperties rp(runTime);

    #include "createMeshes.H"
    simpleControl simple(fluidRegions[0]);
    
    #include "createFields.H"
    #include "createFluidFields.H"
    #include "createSolidFields.H"
    #include "postProcess.H"

    #include "initContinuityErrs.H"
    
    turbulence->validate();
    Info << "Fields created and properties loaded\n" << endl;

    while (runTime.loop())
    {	
        Info<< "Time = " << runTime.timeName() << endl;
        Info<< "TimeStep = " <<  runTime.deltaT().value() << endl;

        // Loading thermal loop control, in case it changed
        fvSolution solutionDict(runTime);

        const dictionary& TempCorr = solutionDict.subDict("TempCorr");

        const int nTempCorr = TempCorr.lookupOrDefault<int>("nTempCorrectors", 1);
        const int thermalBalanceOnly = TempCorr.lookupOrDefault<bool>("thermalBalanceOnly", false);

        // Part solving for temperature and fluid motion
        #include "EDP.H"
        
        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
