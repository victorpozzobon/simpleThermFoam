//- Fluid temperature field
Info<< "Reading field Ta\n" << endl;
volScalarField Ta (IOobject("Ta", runTime.timeName(), fluidRegions[0], IOobject::MUST_READ, IOobject::AUTO_WRITE), fluidRegions[0]);


Info<< "Reading transportProperties for fluid (Air)\n" << endl;

IOdictionary transportPropertiesAir (IOobject("transportProperties",runTime.constant(), fluidRegions[0], IOobject::MUST_READ_IF_MODIFIED, IOobject::NO_WRITE));

// Air density
dimensionedScalar Rhoa("Rhoa", dimDensity, transportPropertiesAir);

// Air thermal conductivity, jsut a scalar to later initialize the actual conductivity field
dimensionedScalar LambdaaFake("Lambdaa", dimPower/dimLength/dimTemperature, transportPropertiesAir);

// Air specific heat
dimensionedScalar Cpa("Cpa", dimSpecificHeatCapacity, transportPropertiesAir);

// Air thermal conductivity field (could be variable, here taken as constant)
volScalarField Lambdaa (IOobject("Lambdaa", runTime.timeName(), fluidRegions[0], IOobject::NO_READ, IOobject::NO_WRITE), fluidRegions[0], LambdaaFake);

