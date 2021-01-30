//- Solid temperature field
Info<< "Reading field Tp\n" << endl;

volScalarField Tp (IOobject("Tp", runTime.timeName(), solidRegions[0], IOobject::MUST_READ, IOobject::AUTO_WRITE), solidRegions[0]);

//- Loading transportProperties for solid
Info<< "Reading transportProperties for solid (Plaquettes)\n" << endl;

IOdictionary transportPropertiesPlaquettes (IOobject("transportProperties",runTime.constant(), solidRegions[0], IOobject::MUST_READ_IF_MODIFIED, IOobject::NO_WRITE));

// Solid density
dimensionedScalar Rhop ("Rhop", dimDensity, transportPropertiesPlaquettes);

// Solid thermal conductivity, jsut a scalar to later initialize the actual conductivity field
dimensionedScalar LambdapFake ("Lambdap", dimPower/dimLength/dimTemperature, transportPropertiesPlaquettes);

// Solid specific heat
dimensionedScalar Cpp ("Cpp", dimSpecificHeatCapacity, transportPropertiesPlaquettes);

// For constant source term, decrepated in favor of variable source term
//dimensionedScalar Qp ("Qp", dimPower/dimVolume, transportPropertiesPlaquettes);

// Solid thermal conductivity field (could be variable, here taken as constant)
volScalarField Lambdap (IOobject("Lambdap", runTime.timeName(), solidRegions[0], IOobject::NO_READ, IOobject::NO_WRITE), solidRegions[0], LambdapFake);

//- Modification for variable heat source term -- VP 2020 March 12th
dimensionedScalar Qp ("Qp", dimPower/dimVolume, transportPropertiesPlaquettes); // => 14.062e6 x 2.50e9 x (0.21 Rho) ^ 0.734 = 1.26e016

dimensionedScalar Ea ("Ea", dimensionSet(1, 2, -2, 0, -1, 0, 0), transportPropertiesPlaquettes); // J/mol => 99800
dimensionedScalar RGP ("RGP", dimensionSet(1, 2, -2, -1, -1, 0, 0), transportPropertiesPlaquettes); // J/mol/K => 8.314

//- End of modification
