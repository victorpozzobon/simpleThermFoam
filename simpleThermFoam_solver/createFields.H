Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        fluidRegions[0],
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    fluidRegions[0]
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        fluidRegions[0],
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    fluidRegions[0]
);

Info<< "Reading/calculating face flux field phi\n" << endl;

surfaceScalarField phi
(
    IOobject
    (
        "phi",
        runTime.timeName(),
        fluidRegions[0],
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    linearInterpolate(U) & fluidRegions[0].Sf()
);

label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, simple.dict(), pRefCell, pRefValue);
fluidRegions[0].setFluxRequired(p.name());


singlePhaseTransportModel laminarTransport(U, phi);

autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phi, laminarTransport)
);

IOMRFZoneList MRF(fluidRegions[0]);
fv::options& fvOptions(fv::options::New(fluidRegions[0]));

if (!fvOptions.optionList::size())
{
    Info << "No finite volume options present" << endl;
}
