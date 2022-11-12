#include "OBJ_Loader.h"
#include "ModelComp.h"
#include "EngMath.h"
class Vector3;
Model::Model(){}
Model::Model(std::string modelPath, bool dyn) {
	ModelPath = modelPath;
	dynamic = dyn;
}
class Transform;
Transform t;

void Model::Init() {
	objl::Loader loader;
	loader.LoadFile(ModelPath);
	for (int i = 0; i < loader.LoadedMaterials.size(); i++) {
		Material mat;
		mat.name = loader.LoadedMaterials[i].name;
		mat.Ka.X = loader.LoadedMaterials[i].Ka.X;
		mat.Ka.Y = loader.LoadedMaterials[i].Ka.Y;
		mat.Ka.Z = loader.LoadedMaterials[i].Ka.Z;
		mat.Ks.X = loader.LoadedMaterials[i].Ks.X;
		mat.Ks.Y = loader.LoadedMaterials[i].Ks.Y;
		mat.Ks.Z = loader.LoadedMaterials[i].Ks.Z;
		mat.Kd.X = loader.LoadedMaterials[i].Kd.X;
		mat.Kd.Y = loader.LoadedMaterials[i].Kd.Y;
		mat.Kd.Z = loader.LoadedMaterials[i].Kd.Z;
		mat.Ns = loader.LoadedMaterials[i].Ns;
		mat.Ni = loader.LoadedMaterials[i].Ni;
		mat.d = loader.LoadedMaterials[i].d;
		mat.illum = loader.LoadedMaterials[i].illum;
		mat.map_Ka = loader.LoadedMaterials[i].map_Ka;
		mat.map_Ks = loader.LoadedMaterials[i].map_Ks;
		mat.map_Kd = loader.LoadedMaterials[i].map_Kd;
		mat.map_Ns = loader.LoadedMaterials[i].map_Ns;
		mat.map_d = loader.LoadedMaterials[i].map_d;
		mat.map_bump = loader.LoadedMaterials[i].map_bump;
		materials.push_back(mat);
	}

	for (int i = 0; i < loader.LoadedVertices.size(); i++) {
		Vector3 v;
		v.X = loader.LoadedVertices[i].Position.X;
		v.Y = loader.LoadedVertices[i].Position.Y;
		v.Z = loader.LoadedVertices[i].Position.Z;
		model.push_back(v);
	}
	for (int i = 0; i < loader.LoadedIndices.size(); i++) {
		indices.push_back(loader.LoadedIndices[i]);
	}
	for (int i = 0; i < loader.LoadedMeshes.size(); i++) {
		Mesh m = Mesh(loader.LoadedMeshes[i]);
		meshes.push_back(loader.LoadedMeshes[i]);
	}
	//calc and push reference to normals.
	// change all things to be pointers to data stored in this instance.
	//for now do a default transform until this gets integrated with entity
	RM.AddDrawable(&model, &indices, &t);
	RM.AddMeshVec(&meshes);
}
void Model::Tick() {
	if (dynamic) {
		//CalcNormals();
	}
}
void Model::CalcNormals() {
	normals = std::vector<Vector3>();
	for (int i = 0; i < indices.size(); i += 3) {
		float normal[3] = {0, 0, 0};
		float v1[3] = { model[i].X, model[i].Y, model[i].Z };
		float v2[3] = { model[i+1].X, model[i+1].Y, model[i+1].Z };
		float v3[3] = { model[i+2].X, model[i+2].Y, model[i+2].Z };


		normalVector(v1, v2, v3, normal);
		normals.push_back(Vector3() = { normal[0], normal[1], normal[2] });
	}
}
Model::~Model() {

}

