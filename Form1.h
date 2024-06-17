#pragma once
#include "Player.h"
#include "GameService.h"
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
			// Inicializa la semilla del generador de n�meros aleatorios con el tiempo actual.
			srand(time(NULL));

			// Crea un objeto Graphics asociado al panel pnl donde se dibujar� el juego.
			panel = pnl->CreateGraphics();

			// Inicializa el administrador de gr�ficos en b�fer.
			space = BufferedGraphicsManager::Current;

			// Asigna un �rea de dibujo en b�fer que coincide con las dimensiones del panel pnl.
			// Allocate: que crea un nuevo objeto BufferedGraphics que encajar� en un �rea espec�fica 
			//del control que proporcionas.
			buffer = space->Allocate(panel, pnl->ClientRectangle);

			// Carga una imagen del archivo "player.png" en un objeto Bitmap que se utilizar� para representar al h�roe.
			bmpPlayer = gcnew Bitmap("assets/playerSprite.png");
			bmpEnemy = gcnew Bitmap("assets/enemySprite.png");

			// Carga una imagen del archivo "fondo.png" en un objeto Bitmap que se utilizar� como fondo del juego.
			bmpMap = gcnew Bitmap("assets/map.png");

			// Crea una instancia de la clase player pasando el ancho y alto de un cuarto de la imagen del h�roe.
			// Esto se usa para dividir la imagen en cuatro partes para la animaci�n.
			player = new Player(bmpPlayer->Width / 4, bmpPlayer->Height / 4);

			sonido = gcnew Media::SoundPlayer();

			gameService = new GameService();
			gameService->createEnemies(bmpEnemy->Width / 4, bmpEnemy->Height / 4);
			//
			//TODO: Add the constructor code here
			//
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

	private:
		Graphics^ panel;                 // Objeto Graphics para dibujar en el panel.
		BufferedGraphicsContext^ space;  // Contexto de gr�ficos en b�fer.
		BufferedGraphics^ buffer;        // B�fer de gr�ficos.
		Bitmap^ bmpPlayer;                 // Imagen del h�roe.
		Bitmap^ bmpMap;                  // Imagen de fondo del juego.
		Bitmap^ bmpEnemy;
		Player* player;                      // Instancia de la clase player para representar al h�roe.


		int indice = 0;
		GameService* gameService;
	private: System::Windows::Forms::Panel^ pnl;




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
		// Limpia el b�fer de gr�ficos con un color de fondo blanco.
		buffer->Graphics->Clear(Color::WhiteSmoke);

		// Dibuja la imagen de fondo en el b�fer de gr�ficos.
		buffer->Graphics->DrawImage(bmpMap, -250, 0, bmpMap->Width, bmpMap->Height );

		gameService->moveEveryThing(buffer->Graphics);

		// Dibuja al h�roe en el b�fer de gr�ficos.
		player->draw(buffer->Graphics, bmpPlayer);
		gameService->drawEveryThing(buffer->Graphics, bmpEnemy);

		if (gameService->getCountEnemiesDelete() == 3) {
			gameService->setIsFinish(true);
			timer1->Enabled = false;
			sonido->Stop();
		}



		// Renderiza el b�fer en el panel.
		buffer->Render(panel);

	}
	private: System::Void Form1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// Maneja el evento KeyDown para mover al h�roe en respuesta a las teclas presionadas.
		switch (e->KeyCode)
		{
		case Keys::A:
			// Mueve al h�roe hacia la izquierda si la tecla 'A' es presionada.
			player->move(buffer->Graphics, 'A');
			break;
		case Keys::D:
			// Mueve al h�roe hacia la derecha si la tecla 'D' es presionada.
			player->move(buffer->Graphics, 'D');
			break;
		case Keys::S:
			// Mueve al h�roe hacia abajo si la tecla 'S' es presionada.
			player->move(buffer->Graphics, 'S');
			break;
		case Keys::W:
			// Mueve al h�roe hacia arriba si la tecla 'W' es presionada.
			player->move(buffer->Graphics, 'W');
			break;
		case Keys::P:
			if (timer1->Enabled)timer1->Enabled = false;
			else timer1->Enabled = true;
			break;
		case Keys::Space:
			//TODO: Implementar funcionalidab
			break;
		}



	}

	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		sonido = gcnew SoundPlayer("assets/menuMusic.wav");
		sonido->Play();
	}
	private: System::Void pnl_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	};
}
