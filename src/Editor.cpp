#include <Knuckles.h>
#include <iostream>
#include <string>

class Editor : public Knuckles::Application {
public:
  Editor(std::string title, int width, int height)
      : Knuckles::Application(title, width, height) {}
  ~Editor() {}

  enum SpawnObject {
    ESphere,
    ECube,
    EPlane,
    EFPSCamera,
    EFollowCamera,
    EorbitCamera
  };

  void AppLoad() override;
  void ImGuiLayerLoad() override;

  void ObjectSpawn(SpawnObject object);
  void ObjectInTree();
  void PropretiesShow(Knuckles::Object *ob);

private:
  Knuckles::Object *mCamera;
  bool mOpen = false;
  bool mProp = false;
  bool mTree = false;
  bool mSaves = false;
  bool mDemo = false;
  char mInpuBuff[50] = "";
  int NOOB;
  int NOOB2;

  std::string mSaveBuff = "Assets/";
  std::string mEndfile = ".Klevel";
  std::string mSavedBuff;
  Knuckles::Object *mObbuff;

  Knuckles::SoundEvent mMusicEvent;
};

void Editor::ImGuiLayerLoad() {
  static char mSave;
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Create")) {
        Knuckles::LevelLoader::LoadLevel(this, "Assets/Default.Klevel");
        mSavedBuff = "Assets/Default.Klevel";
      }
      if (ImGui::MenuItem("Open", "Ctrl+O")) {
        if (mOpen)
          mOpen = false;
        else if (mOpen == false)
          mOpen = true;
      }
      if (ImGui::MenuItem("Save", "Ctrl+S")) {
        Knuckles::LevelLoader::SaveLevel(this, mSavedBuff);
      }
      if (ImGui::MenuItem("Save as..")) {
        if (mSaves)
          mSaves = false;
        else if (mSaves == false)
          mSaves = true;
      }

      if (ImGui::MenuItem("Close")) {
        SetState(EQuit);
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Object")) {
      if (ImGui::MenuItem("Spheres")) {
        ObjectSpawn(ESphere);
      }
      if (ImGui::MenuItem("Plane")) {
        ObjectSpawn(EPlane);
      }
      if (ImGui::MenuItem("FollowObject"))
        ObjectSpawn(EFollowCamera);
      if (ImGui::MenuItem("Camera"))
        ObjectSpawn(EorbitCamera);
      ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Console")) {
    }

    if (ImGui::BeginMenu("Run")) {
      if (ImGui::MenuItem("Play")) {
        SetState(EApplicationplay);
      }
      if (ImGui::MenuItem("Paused")) {
        SetState(EPaused);
        mMusicEvent.SetPaused(true);
      }
      if (ImGui::MenuItem("Editor")) {
        SetState(EEditor);
      }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View")) {
      if (ImGui::MenuItem("Tree")) {
        if (mTree)
          mTree = false;
        else if (mTree == false)
          mTree = true;
      }
      if (ImGui::MenuItem("Propreties")) {
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Demo")) {
      if (mDemo)
        mDemo = false;
      else if (mDemo == false)
        mDemo = true;

      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    if (mDemo)
      ImGui::ShowDemoWindow(&mDemo);

    if (mTree) {
      ImGui::Begin("TREE", &mTree);
      ObjectInTree();
      ImGui::End();
    }

    if (mProp)
      PropretiesShow(mObbuff);

    if (mOpen) {

      ImGui::SetNextWindowSize(ImVec2(400, 100));
      ImGui::Begin("Open File");
      ImGui::InputText("Open: ", mInpuBuff, IM_ARRAYSIZE(mInpuBuff));
      if (ImGui::Button("OPEN")) {
        mSaveBuff = "Assets/";
        mSaveBuff.append(mInpuBuff);
        mSaveBuff.append(mEndfile);
        Knuckles::LevelLoader::LoadLevel(this, mSaveBuff);
        std::cout << "Open: " << mSaveBuff << std::endl;
        mSavedBuff = mSaveBuff;
        mOpen = false;
        char test[] = "";
        for (int i = 0; i < 50; i++)
          mInpuBuff[i] = test[0];

        mSaveBuff.erase();
      }
      ImGui::SameLine();
      if (ImGui::Button("Close")) {
        mOpen = false;
      }
      ImGui::End();
    }

    if (mSaves) {

      ImGui::SetNextWindowSize(ImVec2(400, 100));
      ImGui::Begin("Save as", &mSaves);
      ImGui::InputText("Save name", mInpuBuff, IM_ARRAYSIZE(mInpuBuff));

      if (ImGui::Button("SAVE")) {
        mSaveBuff = "Assets/";
        mSaveBuff.append(mInpuBuff);
        mSaveBuff.append(mEndfile);
        Knuckles::LevelLoader::SaveLevel(this, mSaveBuff);
        std::cout << "Save :" << mSaveBuff << std::endl;
        mSaves = false;
        char test[] = "";
        for (int i = 0; i < 50; i++)
          mInpuBuff[i] = test[0];

        mSaveBuff.erase();
      }
      ImGui::End();
    }
  }
}

void Editor::ObjectSpawn(SpawnObject object) {

  switch (object) {
  case ESphere: {
    new Knuckles::BallObject(this, "Sphere");
    break;
  }
  case ECube:
    break;
  case EPlane:
    NOOB++;
    new Knuckles::PlaneObject(this, "Plane");
    break;
  case EFPSCamera:
    break;
  case EFollowCamera:
    new Knuckles::FollowObject(this, "Follow");
    break;
  case EorbitCamera:
    new Knuckles::CameraObject(this, "Camera");
    break;
  default:
    break;
  }
}

void Editor::PropretiesShow(Knuckles::Object *ob) {
  ImGui::Begin("Propreties", &mProp);
  ImGui::Text("Name:");
  ImGui::SameLine();
  ImGui::Text("%s", ob->GetTitle().c_str());
  ImGui::Text("Position:");
  {
    ImGui::Text("X:");
    ImGui::SameLine();
    ImGui::Text("%s ", std::to_string(ob->GetPosition().x).c_str());
  }
  {
    ImGui::SameLine();
    ImGui::Text("Y:");
    ImGui::SameLine();
    ImGui::Text("%s ", std::to_string(ob->GetPosition().y).c_str());
  }
  {
    ImGui::SameLine();
    ImGui::Text("Z:");
    ImGui::SameLine();
    ImGui::Text("%s", std::to_string(ob->GetPosition().z).c_str());
  }
  {
    ImGui::Text("Image:  ");
    ImGui::SameLine();
    //ImGui::Image(ob->GetMeshComp()->GetTex(), ImVec2(100, 100));
    ImGui::Text("PATH: ");
    ImGui::SameLine();
    //ImGui::Text("%s", ob->GetMesh()->GetFileName().c_str());
  }

  ImGui::End();
}

void Editor::ObjectInTree() {
  for (const auto &ob : GetObjects()) {
    if (ImGui::TreeNode(std::to_string(ob->GetID()).c_str(), "%s",
                        ob->GetTitle().c_str())) {
      static char buff;
      float posx = ob->GetPosition().x;
      float posY = ob->GetPosition().y;
      float posz = ob->GetPosition().z;
      ImGui::SliderFloat("x", &posx, 0.0f, 2000.0f);
      ImGui::SliderFloat("y", &posY, 0.0f, 2000.0f);
      ImGui::SliderFloat("z", &posz, 0.0f, 2000.0f);
      ob->SetPosition(Vector3(posx, posY, posz));
      if (ImGui::Button("Duplicate")) {
        std::string clonename = "Clone ";
        // clonename.push_back(*ob->GetTitle().c_str());
        ob->Clone(clonename);
      }
      ImGui::SameLine();
      if (ImGui::Button("Remove")) {
        ob->Delete();
      }
      ImGui::SameLine();
      if (ImGui::Button("Propreties")) {
        if (mProp)
          mProp = false;
        else if (mProp == false)
          mProp = true;
        mObbuff = ob;
      }
      ImGui::InputText("Rename", &buff, IM_ARRAYSIZE(&buff));
      ImGui::Text("%s", std::to_string(ob->GetID()).c_str());

      ImGui::TreePop();
    }
  }
}

void Editor::AppLoad() {
  KE_INFO("Loading app");
  // Load the level from file
  /*if (!Knuckles::LevelLoader::LoadLevel(this, "Assets/Default.Klevel")) {
    // Create actors
    Knuckles::Object *a = nullptr;
    Quaternion q;
    // MeshComponent *mc = nullptr;

    int count = 0;
    // Setup floor
    const float start = -10.0f;
    const float size = 200.0f;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        a = new Knuckles::PlaneObject(this, "Plane");
        // a = new Knuckles::Grid(this, flo);
        Vector3 pos = Vector3(start + i * size, start + j * size, 0.0f);
        a->SetPosition(pos);
        count++;
      }
    }

    mCamera = new Knuckles::FollowObject(this, "tiger");
    // mCamera = new Knuckles::Camera(this, tigr);

    // Setup lights
    GetRenderer()->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
    Knuckles::DirectionalLight &dir = GetRenderer()->GetDirectionalLight();
    dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
    dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
  }*/
  // Start music
  mMusicEvent = GetAudioSystem()->PlayEvent("event:/Music");
}

Knuckles::Application *Knuckles::CreateApplication() {
  return new Editor("KnucklesEditor", 1024, 768);
}
