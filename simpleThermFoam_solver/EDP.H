//- Entering temperature loop
for (int tempCoor = 0; tempCoor < nTempCorr; tempCoor ++) // Potential use of corrector for the thermal loop, see fvSolution
{
        forAll(solidRegions, i)
        {
            // equation pfor particles temperatures
            // modification MRolland mars2020

            fvScalarMatrix TpEqn
            (
              fvm::ddt(Rhop * Cpp, Tp) - fvm::laplacian(Lambdap, Tp) == Qp * Foam::exp(-Ea / RGP / Tp)
            );

            TpEqn.relax();
            TpEqn.solve();
        }

        forAll(fluidRegions, i)
        {
            //- Gas phase temperature
            // modification MRolland mars2020

            fvScalarMatrix TaEqn
            (
              fvm::ddt(Rhoa * Cpa, Ta) - fvm::laplacian(Lambdaa, Ta) == - Rhoa * Cpa * fvm::div(phi, Ta)
            );

            TaEqn.relax();
            TaEqn.solve();
        }
}//end "for (int tempCoor = 0; tempCoor < nTempCorr; tempCoor ++)"
// Exiting temperature loop
if (not thermalBalanceOnly)
{
    forAll(fluidRegions, i)
    {
            //- Loading the proper fluid mesh
            fvMesh& mesh = fluidRegions[i];
            
            // --- Pressure-velocity SIMPLE corrector
            p.storePrevIter();
            #include "UEqn.H"
            #include "pEqn.H"

            laminarTransport.correct();
            turbulence->correct();
    }
}
