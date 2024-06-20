#pragma once
#include "Player.h"
#include "GameService.h"
#include "Map.h"
#include <iostream>
#include <ctime>


namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Media;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			srand(time(NULL));
			bmpPlayer = gcnew Bitmap("assets/playerSprite.png");
			bmpEnemy = gcnew Bitmap("assets/enemySprite.png");
			bmpMap = gcnew Bitmap("assets/map.png");

			panel = pnl->CreateGraphics();

			space = BufferedGraphicsManager::Current;
			buffer = space->Allocate(panel, pnl->ClientRectangle);
			player = new Player(bmpPlayer->Width / 4, bmpPlayer->Height / 4);
			map = new Map(bmpMap->Width, bmpMap->Height, *player);
			sonido = gcnew Media::SoundPlayer();

			gameService = new GameService();
			gameService->createEnemies(bmpEnemy->Width / 4, bmpEnemy->Height / 4);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private: System::Windows::Forms::ToolStripMenuItem^ menuToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ instruccionesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ salirToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ creditosToolStripMenuItem;
	private: System::Windows::Forms::Panel^ pnlMenu;
	private: System::Windows::Forms::Label^ lblMenu;
	private: System::Windows::Forms::Panel^ pnl;

	private:
		Graphics^ panel;
		BufferedGraphicsContext^ space;
		BufferedGraphics^ buffer;
		Bitmap^ bmpPlayer;
		Bitmap^ bmpMap;
		Bitmap^ bmpEnemy;
		Player* player;


		int indice = 0;
		GameService* gameService;
	private: System::Windows::Forms::Panel^ pnl;



		   Media::SoundPlayer^ pasos;

		   Media::SoundPlayer^ sonido;
		   /// <summary>
		   /// Required designer variable.
		   /// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->pnl = (gcnew System::Windows::Forms::Panel());
			   this->SuspendLayout();
			   // 
			   // timer1
			   // 
			   this->timer1->Enabled = true;
			   this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			   // 
			   // pnl
			   // 
			   this->pnl->AutoSize = true;
			   this->pnl->Location = System::Drawing::Point(2, 2);
			   this->pnl->Name = L"pnl";
			   this->pnl->Size = System::Drawing::Size(727, 391);
			   this->pnl->TabIndex = 0;
			   this->pnl->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pnl_Paint);
			   // 
			   // Form1
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(728, 389);
			   this->Controls->Add(this->pnl);
			   this->Name = L"Form1";
			   this->Text = L"Form1";
			   this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			   this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		buffer->Graphics->Clear(Color::Black);

		//buffer->Graphics->DrawImage(bmpMap, 0, 0, bmpMap->Width/4, bmpMap->Height/4);
		map->draw(buffer->Graphics, bmpMap, *player);

		gameService->moveEveryThing(buffer->Graphics);

		player->draw(buffer->Graphics, bmpPlayer);
		
		gameService->drawEveryThing(buffer->Graphics, bmpEnemy);


		if (gameService->getCountEnemiesDelete() == 3) {
			gameService->setIsFinish(true);
			timer1->Enabled = false;
			sonido->Stop();
		}



		buffer->Render(panel);

	}



	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		sonido = gcnew SoundPlayer("assets/menuMusic.wav");
		pasos = gcnew SoundPlayer("assets/step.wav");

		sonido->Play();
	}
	private: System::Void pnl_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void Form1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::A:
			player->move(buffer->Graphics, 'A');
			pasos->Play();
			break;
		case Keys::D:
			player->move(buffer->Graphics, 'D');
			break;
		case Keys::S:
			player->move(buffer->Graphics, 'S');
			break;
		case Keys::W:
			player->move(buffer->Graphics, 'W');
			break;
		case Keys::P:
			if (timer1->Enabled)timer1->Enabled = false;
			else timer1->Enabled = true;
			break;
		case Keys::Space:
			//TODO: Implementar funcionalidad
			break;
		}
	}

	};
}
