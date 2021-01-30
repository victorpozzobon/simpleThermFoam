//- Solid mesh
const wordList solidsNames(rp["solid"]);
PtrList<fvMesh> solidRegions(solidsNames.size());
forAll(solidsNames, i)
{
        Info<< "Create solid mesh for region " << solidsNames[i]
            << " for time = " << runTime.timeName() << nl << endl;
        solidRegions.set(i, new fvMesh (IOobject(solidsNames[i], runTime.timeName(), runTime, IOobject::MUST_READ)));
}

//- Fluid mesh
const wordList fluidsNames(rp["fluid"]);
PtrList<fvMesh> fluidRegions(fluidsNames.size());
forAll(fluidsNames, i)
{
        Info<< "Create fluid mesh for region " << fluidsNames[i]
            << " for time = " << runTime.timeName() << nl << endl;
        fluidRegions.set(i, new fvMesh (IOobject(fluidsNames[i], runTime.timeName(), runTime, IOobject::MUST_READ)));
}

if (!fluidRegions.size() && !solidRegions.size())
{
    FatalErrorIn(args.executable())
        << "No region meshes present" << exit(FatalError);
}

fvMesh& mesh = fluidRegions.size() ? fluidRegions[0] : solidRegions[0];
