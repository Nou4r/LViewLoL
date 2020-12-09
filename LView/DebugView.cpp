#include "DebugView.h"


const char* DebugView::GetName() {
	return "Debug";
}

void DebugView::DrawSettings(LeagueMemoryReader& reader, UI& ui) {

}

void DrawSpell(Spell spell) {
	if (ImGui::TreeNode(spell.GetTypeStr())) {
		
		ImGui::Button(spell.name.c_str());
		ImGui::DragFloat("Ready At", &spell.readyAt);
		ImGui::DragInt("Level", &spell.level);
		ImGui::TreePop();
	}
}

void DrawMatrix(float* matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		ImGui::BeginGroup();
		for (int j = 0; j < cols; ++j) {
			ImGui::Button(std::to_string(matrix[i*rows + j]).c_str());
			ImGui::SameLine();
		}
		ImGui::EndGroup();
	}
}

void DebugView::DrawPanel(LeagueMemoryReader& reader, UI& ui) {

	ImGui::Begin("Debug");

	ImGui::LabelText("GameTime", "%.2f", reader.gameTime);

	// Draw champs
	for (int i = 0; i < reader.numChampions; ++i) {
		Champion champ = reader.champions[i];
		if (ImGui::TreeNode(champ.name.c_str())) {
			int team = champ.team;
			ImGui::DragInt("Team", &team);
			ImGui::Checkbox("Is Visible", &champ.isVisible);
			ImGui::LabelText("Position", "X:%.2f Y:%.2f Z:%.2f", champ.position.x, champ.position.y, champ.position.z);

			DrawSpell(champ.Q);
			DrawSpell(champ.W);
			DrawSpell(champ.E);
			DrawSpell(champ.R);
			DrawSpell(champ.D);
			DrawSpell(champ.F);

			ImGui::TreePop();
		}
	}

	// Draw renderer
	if (ImGui::TreeNode("Renderer")) {
		
		ImGui::DragInt("Width", &reader.renderer.width);
		ImGui::DragInt("Height", &reader.renderer.height);

		ImGui::Text("View Matrix");
		DrawMatrix(reader.renderer.viewMatrix, 4, 4);
		ImGui::Text("Projection Matrix");
		DrawMatrix(reader.renderer.projMatrix, 4, 4);
		ImGui::TreePop();
	}

	ImGui::End();
}

void DebugView::DrawOverlay(LeagueMemoryReader& reader, ImDrawList* overlayCanvas, UI& ui) {

}