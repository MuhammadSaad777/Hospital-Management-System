#define _CRT_SECURE_NO_WARNINGS

//HEADERS
#include"Menu.h"
#include"Loginwindow.h"
#include"FileHandler.h"
#include<iostream>
#include<fstream>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"InvalidInputException.h"
#include"Validator.h"


using namespace std;
using namespace sf;


//FUNCTION
void DisplayCompleteMenu(Storage<Patient*>& patients, Storage<Doctor*>& doctors, Storage<Appointment*>& appointments,
	Storage<Bill*>& bills, Storage<Prescription*>& prescriptions, Admin*& admin)

{

	sf::RenderWindow window(sf::VideoMode({ 900,500 }), "MediCore Hospital Management System");

	int State = 0;
	float scrollOffset = 0.f;
	int LoginAttempts = 0;
	int rolelogin = 0;

	Patient* Patientcurrent = nullptr;
	Doctor* Doctorcurrent = nullptr;





	//BACKGROUND IMAGES AND SOUNDS
	sf::SoundBuffer buffer_background;
	if (!buffer_background.loadFromFile("backsound.ogg.ogg"))
	{
		return;
	};
	sf::Sound sound_background(buffer_background);
	sound_background.setVolume(100.f);
	sound_background.setLooping(true);
	sound_background.play();



	sf::Texture background_image;
	if (!background_image.loadFromFile("background.png.png"))
	{
		return;
	};
	sf::Sprite background_Sprite(background_image);
	sf::Vector2f targetSize(900.f, 500.f);
	sf::Vector2f textureSize(background_image.getSize());
	background_Sprite.setScale({ targetSize.x / textureSize.x ,targetSize.y / textureSize.y });




	sf::Texture background_image1;
	if (!background_image1.loadFromFile("background1.png.png"))
	{
		return;
	};
	sf::Sprite background_Sprite1(background_image1);
	sf::Vector2f targetSize1(900.f, 500.f);
	sf::Vector2f textureSize1(background_image1.getSize());
	background_Sprite1.setScale({ targetSize1.x / textureSize1.x ,targetSize1.y / textureSize1.y });




	sf::Texture background_image2;
	if (!background_image2.loadFromFile("background2.png.png"))
	{
		return;
	};
	sf::Sprite background_Sprite2(background_image2);
	sf::Vector2f targetSize2(900.f, 500.f);
	sf::Vector2f textureSize2(background_image2.getSize());
	background_Sprite2.setScale({ targetSize2.x / textureSize2.x ,targetSize2.y / textureSize2.y });




	sf::Texture background_image3;
	if (!background_image3.loadFromFile("background3.png.png"))
	{
		cout << "FAILED: background3.png.png" << endl;
		return;
	};
	sf::Sprite background_Sprite3(background_image3);
	sf::Vector2f targetSize3(900.f, 500.f);
	sf::Vector2f textureSize3(background_image3.getSize());
	background_Sprite3.setScale({ targetSize3.x / textureSize3.x ,targetSize3.y / textureSize3.y });



	sf::Font font;
	if (!font.openFromFile("arial.ttf.ttf"))
	{
		return;
	};



	//initial window display
	sf::Text text(font);
	text.setString("Welcome To MediCore Hospital System");
	text.setCharacterSize(36);
	text.setFillColor(sf::Color(255, 215, 0));
	text.setStyle(sf::Text::Bold);
	text.setPosition({ 130.f,40.f });


	sf::Text texts(font);
	texts.setString("Login as:");
	texts.setCharacterSize(44);
	texts.setFillColor(sf::Color(255, 215, 0));
	texts.setStyle(sf::Text::Bold);
	texts.setPosition({ 330.f,100.f });

	Loginwindow idrectangle(250.f, 165.f, 400.f, 45.f, font);
	Loginwindow passrectangle(370.f, 265.f, 400.f, 45.f, font, true);

	//login window display
	sf::Text logintext(font);
	logintext.setString("Enter Your Authentication Credentials : ");
	logintext.setCharacterSize(36);
	logintext.setFillColor(sf::Color::Black);
	logintext.setStyle(sf::Text::Bold);
	logintext.setPosition({ 130.f,60.f });

	sf::Text amount17text(font);
	amount17text.setString("Enter ID : ");
	amount17text.setCharacterSize(32);
	amount17text.setFillColor(sf::Color::Black);
	amount17text.setStyle(sf::Text::Bold);
	amount17text.setPosition({ 100.f,165.f });

	sf::Text loginpassword(font);
	loginpassword.setString("Enter Password : ");
	loginpassword.setCharacterSize(32);
	loginpassword.setFillColor(sf::Color::Black);
	loginpassword.setStyle(sf::Text::Bold);
	loginpassword.setPosition({ 100.f,265.f });

	sf::Text enter17text(font);
	enter17text.setString("");
	enter17text.setCharacterSize(32);
	enter17text.setFillColor(sf::Color::Black);
	enter17text.setStyle(sf::Text::Bold);
	enter17text.setPosition({ 200.f,345.f });

	sf::RectangleShape buttonlogin({ 190.f,60.f });
	buttonlogin.setPosition({ 300.f, 390.f });

	sf::Text loginclick(font);
	loginclick.setString("LOGIN");
	loginclick.setCharacterSize(40);
	loginclick.setFillColor(sf::Color::Black);
	loginclick.setStyle(sf::Text::Bold);
	loginclick.setPosition({ 330.f,397.f });









	//patient window text
	sf::Text patienttext(font);
	patienttext.setString("Welcome, [Patient Name]");
	patienttext.setCharacterSize(44);
	patienttext.setFillColor(sf::Color(255, 215, 0));
	patienttext.setStyle(sf::Text::Bold);
	patienttext.setPosition({ 150.f,20.f });

	sf::Text patienttexts(font);
	patienttexts.setString("Balance: PKR [balance]");
	patienttexts.setCharacterSize(44);
	patienttexts.setFillColor(sf::Color(255, 215, 0));
	patienttexts.setStyle(sf::Text::Bold);
	patienttexts.setPosition({ 150.f,70.f });



	//doctor window text
	sf::Text doctortext(font);
	doctortext.setString("Welcome, Dr. [Name]");
	doctortext.setCharacterSize(44);
	doctortext.setFillColor(sf::Color(255, 215, 0));
	doctortext.setStyle(sf::Text::Bold);
	doctortext.setPosition({ 150.f,20.f });

	sf::Text doctortexts(font);
	doctortexts.setString("Specialization: [spec]");
	doctortexts.setCharacterSize(44);
	doctortexts.setFillColor(sf::Color(255, 215, 0));
	doctortexts.setStyle(sf::Text::Bold);
	doctortexts.setPosition({ 150.f,70.f });



	//admin window text
	sf::Text Admintext(font);
	Admintext.setString("Admin Panel - MediCore");
	Admintext.setCharacterSize(44);
	Admintext.setFillColor(sf::Color(255, 215, 0));
	Admintext.setStyle(sf::Text::Bold);
	Admintext.setPosition({ 150.f,20.f });




	//initial window buttons and texts
	sf::Font buttonfont;
	if (!buttonfont.openFromFile("arial.ttf.ttf"))
	{
		return;
	};
	sf::RectangleShape button1({ 200.f,60.f });
	button1.setPosition({ 320.f, 180.f });





	sf::Text text1(buttonfont);
	text1.setString("PATIENT");
	text1.setCharacterSize(40);
	text1.setFillColor(sf::Color::Red);
	text1.setStyle(sf::Text::Bold);
	text1.setPosition({ 330.f,190.f });


	sf::RectangleShape button2({ 200.f,60.f });
	button2.setPosition({ 320.f, 260.f });


	sf::Text text2(buttonfont);
	text2.setString("DOCTOR");
	text2.setCharacterSize(40);
	text2.setFillColor(sf::Color::Red);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition({ 330.f,270.f });

	sf::RectangleShape button3({ 200.f,60.f });
	button3.setPosition({ 320.f, 340.f });


	sf::Text text3(buttonfont);
	text3.setString("ADMIN");
	text3.setCharacterSize(40);
	text3.setFillColor(sf::Color::Red);
	text3.setStyle(sf::Text::Bold);
	text3.setPosition({ 350.f,350.f });

	sf::RectangleShape button4({ 200.f,60.f });
	button4.setPosition({ 320.f, 420.f });


	sf::Text text4(buttonfont);
	text4.setString("EXIT");
	text4.setCharacterSize(40);
	text4.setFillColor(sf::Color::Red);
	text4.setStyle(sf::Text::Bold);
	text4.setPosition({ 350.f,430.f });





	// patient window buttons and texts
	sf::Font patientfont;
	if (!patientfont.openFromFile("arial.ttf.ttf"))
	{
		return;
	};


	sf::RectangleShape patientbutton1({ 450.f,60.f });
	patientbutton1.setPosition({ 10.f, 150.f });


	sf::Text patienttext1(patientfont);
	patienttext1.setString("Book Appointment");
	patienttext1.setCharacterSize(32);
	patienttext1.setFillColor(sf::Color::Red);
	patienttext1.setStyle(sf::Text::Bold);
	patienttext1.setPosition({ 20.f,160.f });

	sf::RectangleShape patientbutton2({ 450.f,60.f });
	patientbutton2.setPosition({ 10.f, 240.f });


	sf::Text patienttext2(patientfont);
	patienttext2.setString("Cancel Appointment");
	patienttext2.setCharacterSize(40);
	patienttext2.setFillColor(sf::Color::Red);
	patienttext2.setStyle(sf::Text::Bold);
	patienttext2.setPosition({ 20.f,250.f });


	sf::RectangleShape patientbutton3({ 450.f,60.f });
	patientbutton3.setPosition({ 10.f, 330.f });


	sf::Text patienttext3(patientfont);
	patienttext3.setString("View My Appointments");
	patienttext3.setCharacterSize(40);
	patienttext3.setFillColor(sf::Color::Red);
	patienttext3.setStyle(sf::Text::Bold);
	patienttext3.setPosition({ 20.f,340.f });

	sf::RectangleShape patientbutton4({ 500.f,60.f });
	patientbutton4.setPosition({ 10.f, 420.f });


	sf::Text patienttext4(patientfont);
	patienttext4.setString("View My Medical Records");
	patienttext4.setCharacterSize(40);
	patienttext4.setFillColor(sf::Color::Red);
	patienttext4.setStyle(sf::Text::Bold);
	patienttext4.setPosition({ 20.f,430.f });

	sf::RectangleShape patientbutton5({ 300.f,60.f });
	patientbutton5.setPosition({ 550.f, 150.f });


	sf::Text patienttext5(patientfont);
	patienttext5.setString("View My Bills");
	patienttext5.setCharacterSize(40);
	patienttext5.setFillColor(sf::Color::Red);
	patienttext5.setStyle(sf::Text::Bold);
	patienttext5.setPosition({ 560.f,160.f });

	sf::RectangleShape patientbutton6({ 300.f,60.f });
	patientbutton6.setPosition({ 550.f, 240.f });


	sf::Text patienttext6(patientfont);
	patienttext6.setString("Pay Bill");
	patienttext6.setCharacterSize(40);
	patienttext6.setFillColor(sf::Color::Red);
	patienttext6.setStyle(sf::Text::Bold);
	patienttext6.setPosition({ 560.f,250.f });

	sf::RectangleShape patientbutton7({ 300.f,60.f });
	patientbutton7.setPosition({ 550.f, 330.f });


	sf::Text patienttext7(patientfont);
	patienttext7.setString("Top Up Balance");
	patienttext7.setCharacterSize(40);
	patienttext7.setFillColor(sf::Color::Red);
	patienttext7.setStyle(sf::Text::Bold);
	patienttext7.setPosition({ 560.f,340.f });

	sf::RectangleShape patientbutton8({ 300.f,60.f });
	patientbutton8.setPosition({ 550.f, 420.f });
	sf::Font patientfont8;

	sf::Text patienttext8(patientfont);
	patienttext8.setString("Logout");
	patienttext8.setCharacterSize(40);
	patienttext8.setFillColor(sf::Color::Red);
	patienttext8.setStyle(sf::Text::Bold);
	patienttext8.setPosition({ 560.f,430.f });







	//doctor window buttons and texts
	sf::Font doctorfont;
	if (!doctorfont.openFromFile("arial.ttf.ttf"))
	{
		return;
	};


	sf::RectangleShape doctorbutton1({ 520.f,60.f });
	doctorbutton1.setPosition({ 10.f, 150.f });


	sf::Text doctortext1(doctorfont);
	doctortext1.setString("View Today's Appointments");
	doctortext1.setCharacterSize(40);
	doctortext1.setFillColor(sf::Color::Red);
	doctortext1.setStyle(sf::Text::Bold);
	doctortext1.setPosition({ 20.f,160.f });

	sf::RectangleShape doctorbutton2({ 550.f,60.f });
	doctorbutton2.setPosition({ 10.f, 230.f });



	sf::Text doctortext2(doctorfont);
	doctortext2.setString("Mark Appointment Complete");
	doctortext2.setCharacterSize(40);
	doctortext2.setFillColor(sf::Color::Red);
	doctortext2.setStyle(sf::Text::Bold);
	doctortext2.setPosition({ 20.f,235.f });


	sf::RectangleShape doctorbutton3({ 550.f,60.f });
	doctorbutton3.setPosition({ 10.f, 310.f });


	sf::Text doctortext3(doctorfont);
	doctortext3.setString("Mark Appointment No-Show");
	doctortext3.setCharacterSize(40);
	doctortext3.setFillColor(sf::Color::Red);
	doctortext3.setStyle(sf::Text::Bold);
	doctortext3.setPosition({ 20.f,315.f });

	sf::RectangleShape doctorbutton4({ 340.f,60.f });
	doctorbutton4.setPosition({ 550.f, 150.f });


	sf::Text doctortext4(doctorfont);
	doctortext4.setString("Write Prescription");
	doctortext4.setCharacterSize(40);
	doctortext4.setFillColor(sf::Color::Red);
	doctortext4.setStyle(sf::Text::Bold);
	doctortext4.setPosition({ 560.f,155.f });

	sf::RectangleShape doctorbutton5({ 550.f,60.f });
	doctorbutton5.setPosition({ 10.f, 390.f });


	sf::Text doctortext5(doctorfont);
	doctortext5.setString("View Patient Medical History");
	doctortext5.setCharacterSize(40);
	doctortext5.setFillColor(sf::Color::Red);
	doctortext5.setStyle(sf::Text::Bold);
	doctortext5.setPosition({ 20.f,395.f });

	sf::RectangleShape doctorbutton6({ 200.f,60.f });
	doctorbutton6.setPosition({ 600.f, 250.f });


	sf::Text doctortext6(doctorfont);
	doctortext6.setString("Logout");
	doctortext6.setCharacterSize(40);
	doctortext6.setFillColor(sf::Color::Red);
	doctortext6.setStyle(sf::Text::Bold);
	doctortext6.setPosition({ 610.f,255.f });


	//admin window buttons and texts
	sf::Font Adminfont;
	if (!Adminfont.openFromFile("arial.ttf.ttf"))
	{
		return;
	};


	sf::RectangleShape Adminbutton1({ 240.f,60.f });
	Adminbutton1.setPosition({ 10.f, 90.f });


	sf::Text Admintext1(Adminfont);
	Admintext1.setString("Add Doctor");
	Admintext1.setCharacterSize(40);
	Admintext1.setFillColor(sf::Color::Red);
	Admintext1.setStyle(sf::Text::Bold);
	Admintext1.setPosition({ 20.f,100.f });

	sf::RectangleShape Adminbutton2({ 320.f,60.f });
	Adminbutton2.setPosition({ 10.f, 180.f });


	sf::Text Admintext2(Adminfont);
	Admintext2.setString("Remove Doctor");
	Admintext2.setCharacterSize(40);
	Admintext2.setFillColor(sf::Color::Red);
	Admintext2.setStyle(sf::Text::Bold);
	Admintext2.setPosition({ 20.f,190.f });


	sf::RectangleShape Adminbutton3({ 340.f,60.f });
	Adminbutton3.setPosition({ 10.f, 270.f });


	sf::Text Admintext3(Adminfont);
	Admintext3.setString("View All Patients");
	Admintext3.setCharacterSize(40);
	Admintext3.setFillColor(sf::Color::Red);
	Admintext3.setStyle(sf::Text::Bold);
	Admintext3.setPosition({ 20.f,280.f });

	sf::RectangleShape Adminbutton4({ 340.f,60.f });
	Adminbutton4.setPosition({ 10.f, 360.f });


	sf::Text Admintext4(Adminfont);
	Admintext4.setString("View All Doctors");
	Admintext4.setCharacterSize(40);
	Admintext4.setFillColor(sf::Color::Red);
	Admintext4.setStyle(sf::Text::Bold);
	Admintext4.setPosition({ 20.f,370.f });

	sf::RectangleShape Adminbutton5({ 420.f,53.f });
	Adminbutton5.setPosition({ 10.f, 440.f });


	sf::Text Admintext5(Adminfont);
	Admintext5.setString("View All Appointments");
	Admintext5.setCharacterSize(40);
	Admintext5.setFillColor(sf::Color::Red);
	Admintext5.setStyle(sf::Text::Bold);
	Admintext5.setPosition({ 20.f,443.f });

	sf::RectangleShape Adminbutton6({ 350.f,60.f });
	Adminbutton6.setPosition({ 450.f, 90.f });


	sf::Text Admintext6(Adminfont);
	Admintext6.setString("View Unpaid Bills");
	Admintext6.setCharacterSize(40);
	Admintext6.setFillColor(sf::Color::Red);
	Admintext6.setStyle(sf::Text::Bold);
	Admintext6.setPosition({ 460.f,100.f });

	sf::RectangleShape Adminbutton7({ 360.f,60.f });
	Adminbutton7.setPosition({ 450.f, 180.f });


	sf::Text Admintext7(Adminfont);
	Admintext7.setString("Discharge Patient");
	Admintext7.setCharacterSize(40);
	Admintext7.setFillColor(sf::Color::Red);
	Admintext7.setStyle(sf::Text::Bold);
	Admintext7.setPosition({ 460.f,190.f });

	sf::RectangleShape Adminbutton8({ 370.f,60.f });
	Adminbutton8.setPosition({ 450.f, 270.f });


	sf::Text Admintext8(Adminfont);
	Admintext8.setString("View Security Log");
	Admintext8.setCharacterSize(40);
	Admintext8.setFillColor(sf::Color::Red);
	Admintext8.setStyle(sf::Text::Bold);
	Admintext8.setPosition({ 460.f,280.f });

	sf::RectangleShape Adminbutton9({ 430.f,60.f });
	Adminbutton9.setPosition({ 450.f, 360.f });


	sf::Text Admintext9(Adminfont);
	Admintext9.setString("Generate Daily Report");
	Admintext9.setCharacterSize(40);
	Admintext9.setFillColor(sf::Color::Red);
	Admintext9.setStyle(sf::Text::Bold);
	Admintext9.setPosition({ 460.f,370.f });

	sf::RectangleShape Adminbutton10({ 170.f,53.f });
	Adminbutton10.setPosition({ 450.f, 440.f });


	sf::Text Admintext10(Adminfont);
	Admintext10.setString("Logout");
	Admintext10.setCharacterSize(40);
	Admintext10.setFillColor(sf::Color::Red);
	Admintext10.setStyle(sf::Text::Bold);
	Admintext10.setPosition({ 460.f,443.f });



	//text on all patient screens 

	sf::Text patientmessage(font);
	patientmessage.setString("");
	patientmessage.setCharacterSize(32);
	patientmessage.setFillColor(sf::Color(255, 140, 0));
	patientmessage.setStyle(sf::Text::Bold);
	patientmessage.setPosition({ 150.f,400.f });

	//admin buttons further logic
	Loginwindow docnamebox31(400.f, 80.f, 350.f, 40.f, font);
	Loginwindow docspecbox31(400.f, 150.f, 350.f, 40.f, font);
	Loginwindow doccontbox31(400.f, 220.f, 350.f, 40.f, font);
	Loginwindow docpassbox31(400.f, 290.f, 350.f, 40.f, font, true);
	Loginwindow docfeebox31(400.f, 360.f, 350.f, 40.f, font);



	sf::Text docname31(font);
	docname31.setString("Doctor Name:");
	docname31.setCharacterSize(32);
	docname31.setFillColor(sf::Color(255, 140, 0));
	docname31.setPosition({ 50.f, 85.f });

	sf::Text docspec31(font);
	docspec31.setString("Specialization:");
	docspec31.setCharacterSize(32);
	docspec31.setFillColor(sf::Color(255, 140, 0));
	docspec31.setPosition({ 50.f, 155.f });

	sf::Text doccont31(font);
	doccont31.setString("Contact (11 digits):");
	doccont31.setCharacterSize(32);
	doccont31.setFillColor(sf::Color(255, 140, 0));
	doccont31.setPosition({ 50.f, 225.f });

	sf::Text docpass31(font);
	docpass31.setString("Password (min 6 chars):");
	docpass31.setCharacterSize(32);
	docpass31.setFillColor(sf::Color(255, 140, 0));
	docpass31.setPosition({ 50.f, 295.f });

	sf::Text docfee31(font);
	docfee31.setString("Consultation Fee:");
	docfee31.setCharacterSize(32);
	docfee31.setFillColor(sf::Color(255, 140, 0));
	docfee31.setPosition({ 50.f, 365.f });

	sf::RectangleShape addDocbutton({ 180.f, 45.f });
	addDocbutton.setPosition({ 350.f, 410.f });
	addDocbutton.setFillColor(sf::Color(0, 150, 0));

	sf::Text doctbutton31(font);
	doctbutton31.setString("ADD");
	doctbutton31.setCharacterSize(26);
	doctbutton31.setFillColor(sf::Color::White);
	doctbutton31.setStyle(sf::Text::Bold);
	doctbutton31.setPosition({ 400.f, 415.f });

	Loginwindow removedocbox32(450.f, 250.f, 350.f, 45.f, font);



	sf::Text removedoc32(font);
	removedoc32.setString("Enter Doctor ID to remove:");
	removedoc32.setCharacterSize(32);
	removedoc32.setFillColor(sf::Color(255, 140, 0));
	removedoc32.setPosition({ 50.f, 255.f });

	sf::RectangleShape removedocbutton32({ 200.f, 50.f });
	removedocbutton32.setPosition({ 340.f, 330.f });
	removedocbutton32.setFillColor(sf::Color::White);

	sf::Text removedocbuttontext32(font);
	removedocbuttontext32.setString("REMOVE");
	removedocbuttontext32.setCharacterSize(32);
	removedocbuttontext32.setFillColor(sf::Color(255, 140, 0));
	removedocbuttontext32.setStyle(sf::Text::Bold);
	removedocbuttontext32.setPosition({ 365.f, 338.f });



	Loginwindow dischargebox37(400.f, 100.f, 350.f, 45.f, font);


	sf::Text dischargeid37(font);
	dischargeid37.setString("Enter Patient ID:");
	dischargeid37.setCharacterSize(32);
	dischargeid37.setFillColor(sf::Color(255, 140, 0));
	dischargeid37.setStyle(sf::Text::Bold);
	dischargeid37.setPosition({ 100.f, 100.f });

	sf::RectangleShape dischargebutton37({ 200.f, 50.f });
	dischargebutton37.setPosition({ 350.f, 200.f });
	dischargebutton37.setFillColor(sf::Color::White);

	sf::Text dischargebuttontext37(font);
	dischargebuttontext37.setString("DISCHARGE");
	dischargebuttontext37.setCharacterSize(28);
	dischargebuttontext37.setFillColor(sf::Color(255, 140, 0));
	dischargebuttontext37.setStyle(sf::Text::Bold);
	dischargebuttontext37.setPosition({ 360.f, 208.f });


	//admin buttons results
	sf::Text adminresulttext371(font);
	adminresulttext371.setString("");
	adminresulttext371.setCharacterSize(32);
	adminresulttext371.setFillColor(sf::Color::Yellow);
	adminresulttext371.setPosition({ 50.f, 460.f });

	sf::Text adminresulttext372(font);
	adminresulttext372.setString("");
	adminresulttext372.setCharacterSize(32);
	adminresulttext372.setFillColor(sf::Color::Yellow);
	adminresulttext372.setPosition({ 50.f, 460.f });

	sf::Text adminresulttext377(font);
	adminresulttext377.setString("");
	adminresulttext377.setCharacterSize(32);
	adminresulttext377.setFillColor(sf::Color::Yellow);
	adminresulttext377.setPosition({ 50.f, 460.f });


	//patient buttons further logic
	Loginwindow bookspecbox11(150.f, 130.f, 250.f, 40.f, font);
	Loginwindow bookdocbox11(150.f, 220.f, 250.f, 40.f, font);
	Loginwindow bookdatebox11(150.f, 310.f, 250.f, 40.f, font);
	Loginwindow bookslotbox11(150.f, 400.f, 250.f, 40.f, font);


	sf::Text bookspec11(font);
	bookspec11.setString("Specialization:");
	bookspec11.setCharacterSize(28);
	bookspec11.setFillColor(sf::Color(255, 140, 0));
	bookspec11.setPosition({ 150.f, 90.f });

	sf::Text bookdocid11(font);
	bookdocid11.setString("Doctor ID:");
	bookdocid11.setCharacterSize(28);
	bookdocid11.setFillColor(sf::Color(255, 140, 0));
	bookdocid11.setPosition({ 150.f, 180.f });

	sf::Text bookdate11(font);
	bookdate11.setString("Date (DD-MM-YYYY):");
	bookdate11.setCharacterSize(28);
	bookdate11.setFillColor(sf::Color(255, 140, 0));
	bookdate11.setPosition({ 150.f, 270.f });

	sf::Text bookslot11(font);
	bookslot11.setString("Time Slot (e.g. 09:00):");
	bookslot11.setCharacterSize(28);
	bookslot11.setFillColor(sf::Color(255, 140, 0));
	bookslot11.setPosition({ 150.f, 360.f });

	sf::RectangleShape bookbutton11({ 180.f, 45.f });
	bookbutton11.setPosition({ 680.f, 400.f });
	bookbutton11.setFillColor(sf::Color(0, 150, 0));

	sf::Text bookbuttontext11(font);
	bookbuttontext11.setString("BOOK");
	bookbuttontext11.setCharacterSize(26);
	bookbuttontext11.setFillColor(sf::Color::White);
	bookbuttontext11.setStyle(sf::Text::Bold);
	bookbuttontext11.setPosition({ 710.f, 408.f });


	sf::Text bookdoclistshow11(font);
	bookdoclistshow11.setString("");
	bookdoclistshow11.setCharacterSize(18);
	bookdoclistshow11.setFillColor(sf::Color::White);
	bookdoclistshow11.setPosition({ 400.f, 100.f });


	Loginwindow cancelbox12(330.f, 270.f, 350.f, 45.f, font);


	sf::Text canceltext12(font);
	canceltext12.setString("Enter Appointment ID:");
	canceltext12.setCharacterSize(28);
	canceltext12.setFillColor(sf::Color(255, 140, 0));
	canceltext12.setPosition({ 50.f, 270.f });

	sf::RectangleShape cancelbutton12({ 200.f, 50.f });
	cancelbutton12.setPosition({ 350.f, 400.f });
	cancelbutton12.setFillColor(sf::Color(200, 0, 0));

	sf::Text cancelbuttontext12(font);
	cancelbuttontext12.setString("CANCEL");
	cancelbuttontext12.setCharacterSize(28);
	cancelbuttontext12.setFillColor(sf::Color::White);
	cancelbuttontext12.setStyle(sf::Text::Bold);
	cancelbuttontext12.setPosition({ 365.f, 408.f });


	Loginwindow paybillbox16(300.f, 220.f, 350.f, 45.f, font);



	sf::Text paybilltext16(font);
	paybilltext16.setString("Enter Bill ID:");
	paybilltext16.setCharacterSize(28);
	paybilltext16.setFillColor(sf::Color(255, 140, 0));
	paybilltext16.setPosition({ 50.f, 225.f });

	sf::RectangleShape paybillbutton16({ 200.f, 50.f });
	paybillbutton16.setPosition({ 350.f, 300.f });
	paybillbutton16.setFillColor(sf::Color(0, 150, 0));

	sf::Text paybillbuttontext16(font);
	paybillbuttontext16.setString("PAY");
	paybillbuttontext16.setCharacterSize(28);
	paybillbuttontext16.setFillColor(sf::Color::White);
	paybillbuttontext16.setStyle(sf::Text::Bold);
	paybillbuttontext16.setPosition({ 415.f, 308.f });




	Loginwindow topupbox17(360.f, 220.f, 350.f, 45.f, font);



	sf::Text topuptext17(font);
	topuptext17.setString("Enter Amount (PKR):");
	topuptext17.setCharacterSize(28);
	topuptext17.setFillColor(sf::Color(255, 140, 0));
	topuptext17.setPosition({ 50.f, 225.f });

	sf::RectangleShape topupbutton17({ 200.f, 50.f });
	topupbutton17.setPosition({ 350.f, 300.f });
	topupbutton17.setFillColor(sf::Color(0, 150, 0));

	sf::Text topupbuttontext17(font);
	topupbuttontext17.setString("CONFIRM");
	topupbuttontext17.setCharacterSize(28);
	topupbuttontext17.setFillColor(sf::Color::White);
	topupbuttontext17.setStyle(sf::Text::Bold);
	topupbuttontext17.setPosition({ 365.f, 308.f });


	//patient buttons result display
	sf::Text resulttext11(font);
	resulttext11.setString("");
	resulttext11.setCharacterSize(22);
	resulttext11.setFillColor(sf::Color::Yellow);
	resulttext11.setPosition({ 50.f, 460.f });

	sf::Text resulttext12(font);
	resulttext12.setString("");
	resulttext12.setCharacterSize(22);
	resulttext12.setFillColor(sf::Color::Yellow);
	resulttext12.setPosition({ 50.f, 460.f });


	sf::Text resulttext16(font);
	resulttext16.setString("");
	resulttext16.setCharacterSize(22);
	resulttext16.setFillColor(sf::Color::Yellow);
	resulttext16.setPosition({ 50.f, 460.f });

	sf::Text resulttext17(font);
	resulttext17.setString("");
	resulttext17.setCharacterSize(22);
	resulttext17.setFillColor(sf::Color::Yellow);
	resulttext17.setPosition({ 50.f, 460.f });



	//doctor buttons further logic
	Loginwindow markcompletebox22(370.f, 250.f, 350.f, 45.f, font);


	sf::Text markcompletetext22(font);
	markcompletetext22.setString("Enter Appointment ID:");
	markcompletetext22.setCharacterSize(26);
	markcompletetext22.setFillColor(sf::Color(255, 140, 0));
	markcompletetext22.setPosition({ 50.f, 255.f });

	sf::RectangleShape markcompletebutton22({ 200.f, 50.f });
	markcompletebutton22.setPosition({ 350.f, 330.f });
	markcompletebutton22.setFillColor(sf::Color(0, 150, 0));

	sf::Text markcompletebuttontext22(font);
	markcompletebuttontext22.setString("COMPLETE");
	markcompletebuttontext22.setCharacterSize(26);
	markcompletebuttontext22.setFillColor(sf::Color::White);
	markcompletebuttontext22.setStyle(sf::Text::Bold);
	markcompletebuttontext22.setPosition({ 360.f, 338.f });



	Loginwindow marknoshowbox23(370.f, 250.f, 350.f, 45.f, font);



	sf::Text marknoshowtext23(font);
	marknoshowtext23.setString("Enter Appointment ID:");
	marknoshowtext23.setCharacterSize(26);
	marknoshowtext23.setFillColor(sf::Color(255, 140, 0));
	marknoshowtext23.setPosition({ 50.f, 255.f });

	sf::RectangleShape marknoshbutton23({ 200.f, 50.f });
	marknoshbutton23.setPosition({ 350.f, 330.f });
	marknoshbutton23.setFillColor(sf::Color(200, 100, 0));

	sf::Text marknoshbuttontext23(font);
	marknoshbuttontext23.setString("NO-SHOW");
	marknoshbuttontext23.setCharacterSize(26);
	marknoshbuttontext23.setFillColor(sf::Color::White);
	marknoshbuttontext23.setStyle(sf::Text::Bold);
	marknoshbuttontext23.setPosition({ 365.f, 338.f });




	Loginwindow prescappbox24(300.f, 130.f, 350.f, 40.f, font);
	Loginwindow prescmedbox24(330.f, 230.f, 550.f, 40.f, font);
	Loginwindow prescnotesbox24(300.f, 330.f, 550.f, 40.f, font);



	sf::Text prescapptext24(font);
	prescapptext24.setString("Appointment ID:");
	prescapptext24.setCharacterSize(24);
	prescapptext24.setFillColor(sf::Color(255, 140, 0));
	prescapptext24.setPosition({ 50.f, 135.f });

	sf::Text prescmedtext24(font);
	prescmedtext24.setString("Medicines (e.g. Med1 500mg):");
	prescmedtext24.setCharacterSize(22);
	prescmedtext24.setFillColor(sf::Color(255, 140, 0));
	prescmedtext24.setPosition({ 20.f, 235.f });

	sf::Text prescnotestext24(font);
	prescnotestext24.setString("Notes:");
	prescnotestext24.setCharacterSize(24);
	prescnotestext24.setFillColor(sf::Color(255, 140, 0));
	prescnotestext24.setPosition({ 50.f, 335.f });

	sf::RectangleShape prescbutton24({ 200.f, 50.f });
	prescbutton24.setPosition({ 350.f, 425.f });
	prescbutton24.setFillColor(sf::Color(0, 150, 0));

	sf::Text prescbuttontext24(font);
	prescbuttontext24.setString("SAVE");
	prescbuttontext24.setCharacterSize(28);
	prescbuttontext24.setFillColor(sf::Color::White);
	prescbuttontext24.setStyle(sf::Text::Bold);
	prescbuttontext24.setPosition({ 400.f, 430.f });



	Loginwindow pathistorybox25(300.f, 200.f, 350.f, 45.f, font);



	sf::Text pathistorytext25(font);
	pathistorytext25.setString("Enter Patient ID:");
	pathistorytext25.setCharacterSize(26);
	pathistorytext25.setFillColor(sf::Color(255, 140, 0));
	pathistorytext25.setPosition({ 100.f, 205.f });

	sf::RectangleShape historybutton25({ 200.f, 50.f });
	historybutton25.setPosition({ 350.f, 270.f });
	historybutton25.setFillColor(sf::Color(0, 100, 200));

	sf::Text histbuttontext25(font);
	histbuttontext25.setString("VIEW");
	histbuttontext25.setCharacterSize(28);
	histbuttontext25.setFillColor(sf::Color::White);
	histbuttontext25.setStyle(sf::Text::Bold);
	histbuttontext25.setPosition({ 400.f, 278.f });

	sf::Text historyresult25(font);
	historyresult25.setString("");
	historyresult25.setCharacterSize(24);
	historyresult25.setFillColor(sf::Color(255, 140, 0));
	historyresult25.setPosition({ 50.f, 340.f });

	//doctor buttons result text
	sf::Text docresulttext22(font);
	docresulttext22.setString("");
	docresulttext22.setCharacterSize(22);
	docresulttext22.setFillColor(sf::Color::Yellow);
	docresulttext22.setPosition({ 50.f, 460.f });


	sf::Text docresulttext23(font);
	docresulttext23.setString("");
	docresulttext23.setCharacterSize(22);
	docresulttext23.setFillColor(sf::Color::Yellow);
	docresulttext23.setPosition({ 50.f, 460.f });

	sf::Text docresulttext24(font);
	docresulttext24.setString("");
	docresulttext24.setCharacterSize(22);
	docresulttext24.setFillColor(sf::Color::Yellow);
	docresulttext24.setPosition({ 50.f, 460.f });

	sf::Text docresulttext25(font);
	docresulttext25.setString("");
	docresulttext25.setCharacterSize(22);
	docresulttext25.setFillColor(sf::Color::Yellow);
	docresulttext25.setPosition({ 50.f, 460.f });







	//whole loop for window functionality
	while (window.isOpen())
	{

		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			//replace input with stars for privacy
			//login privacy
			if (State == 5)
			{
				idrectangle.manageevents(*event);
				passrectangle.manageevents(*event);

			}


			//patient privacy
			if (State == 11)
			{
				bookspecbox11.manageevents(*event);
				bookdocbox11.manageevents(*event);
				bookdatebox11.manageevents(*event);
				bookslotbox11.manageevents(*event);
			}
			if (State == 17)
			{
				topupbox17.manageevents(*event);
			}
			if (State == 16)
			{
				paybillbox16.manageevents(*event);
			}
			if (State == 12)
			{
				cancelbox12.manageevents(*event);
			}




			//doctor privacy
			if (State == 22)
			{
				markcompletebox22.manageevents(*event);
			}
			if (State == 23)
			{
				marknoshowbox23.manageevents(*event);
			}
			if (State == 24)
			{
				prescappbox24.manageevents(*event);
				prescmedbox24.manageevents(*event);
				prescnotesbox24.manageevents(*event);
			}
			if (State == 25)
			{
				pathistorybox25.manageevents(*event);
			}





			//admin privacy
			if (State == 31)
			{
				docnamebox31.manageevents(*event);
				docspecbox31.manageevents(*event);
				doccontbox31.manageevents(*event);
				docpassbox31.manageevents(*event);
				docfeebox31.manageevents(*event);
			}
			if (State == 32)
			{
				removedocbox32.manageevents(*event);
			}
			if (State == 37)
			{
				dischargebox37.manageevents(*event);
			}







			//loop to detect pressing of keys
			if (event->is<sf::Event::KeyPressed>())
			{

				// window hovering logic
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
				{
					scrollOffset += 30.f;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
				{
					scrollOffset -= 30.f;
					if (scrollOffset < 0.f)
					{
						scrollOffset = 0.f;
					}
				}



				//return to earlier state by pressing escape button
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				{
					if (State == 11 || State == 12 || State == 13 || State == 14 || State == 15 || State == 16 || State == 17)
					{
						State = 1;
						scrollOffset = 0.f;
					}
					else if (State == 21 || State == 22 || State == 23 || State == 24 || State == 25)
					{
						State = 2;
						scrollOffset = 0.f;
					}
					else if (State == 31 || State == 32 || State == 33 || State == 34 || State == 35 || State == 36 || State == 37 || State == 38 || State == 39)
					{
						State = 3;
						scrollOffset = 0.f;
					}
					else if (State == 1 || State == 2 || State == 3)
					{
						State = 0;
						scrollOffset = 0.f;
					}
					else if (State == 5)
					{
						State = 0;
						scrollOffset = 0.f;
					}
					else if (State == 0)
					{
						window.close();
					}

				}


			}


			//mouse wheel scrolling detect
			if (const auto* scrollEvent = event->getIf<sf::Event::MouseWheelScrolled>())
			{
				if (scrollEvent->wheel == sf::Mouse::Wheel::Vertical)
				{
					//60 pixel jump on movement
					scrollOffset += scrollEvent->delta * 60.f;
					//upper boundary of window, no lower boundary setted.
					if (scrollOffset < 0.f)
					{
						scrollOffset = 0.f;
					}
				}
			}




			if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
			{

				//only detect mouse click if left click done
				if (mouseClick->button == sf::Mouse::Button::Left)
				{

					//convert pixel position into coordinates
					sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));


					//checks clicking of buttons in initial window
					if (State == 0)
					{

						//checks if click was within button range
						if (button1.getGlobalBounds().contains(mousePosition))
						{

							rolelogin = 1;
							LoginAttempts = 0;
							idrectangle.cleartext();
							passrectangle.cleartext();
							idrectangle.setstatus(true);
							passrectangle.setstatus(false);
							enter17text.setString("");
							State = 5;


						}
						else if (button2.getGlobalBounds().contains(mousePosition))
						{

							rolelogin = 2;
							LoginAttempts = 0;
							idrectangle.cleartext();
							passrectangle.cleartext();
							idrectangle.setstatus(true);
							passrectangle.setstatus(false);
							enter17text.setString("");
							State = 5;
						}
						else if (button3.getGlobalBounds().contains(mousePosition))
						{

							rolelogin = 3;
							LoginAttempts = 0;
							idrectangle.cleartext();
							passrectangle.cleartext();
							idrectangle.setstatus(true);
							passrectangle.setstatus(false);
							enter17text.setString("");
							State = 5;
						}
						else if (button4.getGlobalBounds().contains(mousePosition))
						{
							window.close();
						}

					}



					//patient click detection

					else if (State == 1)
					{
						if (patientbutton1.getGlobalBounds().contains(mousePosition))
						{

							scrollOffset = 0.f;
							State = 11;
						}
						else if (patientbutton2.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 12;
							cancelbox12.cleartext();
							cancelbox12.setstatus(true);
						}
						else if (patientbutton3.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 13;
						}
						else if (patientbutton4.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 14;
						}
						else if (patientbutton5.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 15;
						}
						else if (patientbutton6.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 16;
							paybillbox16.cleartext();
							paybillbox16.setstatus(true);
						}
						else if (patientbutton7.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;

							State = 17;
							topupbox17.cleartext();
							topupbox17.setstatus(true);
						}
						else if (patientbutton8.getGlobalBounds().contains(mousePosition))
						{
							Patientcurrent = nullptr;
							scrollOffset = 0.f;
							State = 0;
						}
					}

					//doctor click detection
					else if (State == 2)
					{
						if (doctorbutton1.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 21;
						}
						else if (doctorbutton2.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 22;
							markcompletebox22.cleartext();
							markcompletebox22.setstatus(true);
						}
						else if (doctorbutton3.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 23;
							marknoshowbox23.cleartext();
							marknoshowbox23.setstatus(true);
						}
						else if (doctorbutton4.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 24;
							prescappbox24.setstatus(true);
							prescmedbox24.setstatus(false);
							prescnotesbox24.setstatus(false);
						}
						else if (doctorbutton5.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 25;
							pathistorybox25.cleartext();
							pathistorybox25.setstatus(true);

						}
						else if (doctorbutton6.getGlobalBounds().contains(mousePosition))
						{
							Doctorcurrent = nullptr;
							scrollOffset = 0.f;
							State = 0;
						}

					}




					//admin click detection
					else if (State == 3)
					{
						if (Adminbutton1.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 31;
							docnamebox31.setstatus(true);
							docspecbox31.setstatus(false);
							doccontbox31.setstatus(false);
							docpassbox31.setstatus(false);
							docfeebox31.setstatus(false);
						}
						else if (Adminbutton2.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 32;
							removedocbox32.cleartext();
							removedocbox32.setstatus(true);
						}
						else if (Adminbutton3.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 33;
						}
						else if (Adminbutton4.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 34;
						}
						else if (Adminbutton5.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 35;
						}
						else if (Adminbutton6.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 36;
						}
						else if (Adminbutton7.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 37;
							dischargebox37.cleartext();
							dischargebox37.setstatus(true);
						}
						else if (Adminbutton8.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 38;
						}
						else if (Adminbutton9.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 39;
						}
						else if (Adminbutton10.getGlobalBounds().contains(mousePosition))
						{
							scrollOffset = 0.f;
							State = 0;
						}
					}


					//login window click detection
					else if (State == 5)
					{
						//logic to change state when id rectangle is clicked
						if (idrectangle.getGlobalBounds().contains(mousePosition))
						{
							idrectangle.setstatus(true);
							passrectangle.setstatus(false);

						}
						//logic to change state when password rectangle is clicked
						else if (passrectangle.getGlobalBounds().contains(mousePosition))
						{
							idrectangle.setstatus(false);
							passrectangle.setstatus(true);
						}



						//click detection after login button press
						//check if login successful move to next state
						//else remain on that state, return to previous state on 3 wrong tries
						else if (buttonlogin.getGlobalBounds().contains(mousePosition))
						{
							int userid = atoi(idrectangle.getvalue());
							const char* userpass = passrectangle.getvalue();
							bool correct = false;

							//check patient credentials are fine 
							if (rolelogin == 1)
							{
								Patient* patfind = patients.findbyid(userid);
								if (patfind != nullptr)
								{
									bool comparison = true;
									const char* correctpass = patfind->getPass();
									int i = 0;
									while (userpass[i] != '\0' && correctpass[i] != '\0')
									{
										if (userpass[i] != correctpass[i])
										{
											comparison = false;
											break;
										}
										i++;
									}
									if (userpass[i] != '\0' || correctpass[i] != '\0')
									{
										comparison = false;
									}

									//printing initials of next patient state window
									if (comparison == true)
									{
										Patientcurrent = patfind;
										char greeting[100] = "WELCOME, ";
										int gindex = 9;
										const char* patname = patfind->getName();
										for (int k = 0;patname[k] != '\0';k++)
										{
											greeting[gindex] = patname[k];
											gindex++;
										}
										greeting[gindex] = '\0';
										patienttext.setString(greeting);
										char patbalance[100] = "BALANCE: PKR ";
										int balan = (int)patfind->getbalance();
										char balanval[50];
										int bali = 0;
										if (balan == 0)
										{
											balanval[bali++] = '0';
										}
										else
										{
											char imag[40];
											int imagi = 0;
											while (balan > 0)
											{
												imag[imagi++] = '0' + balan % 10;
												balan = balan / 10;

											}
											for (int l = imagi - 1;l >= 0;l--)
											{
												balanval[bali++] = imag[l];


											}
										}
										balanval[bali] = '\0';

										int newval = 13;
										for (int m = 0; balanval[m] != '\0';m++)
										{
											patbalance[newval] = balanval[m];
											newval++;
										}
										patbalance[newval] = '\0';
										patienttexts.setString(patbalance);
										correct = true;
										State = 1;




									}

								}
							}
							//doctor credentials check
							else if (rolelogin == 2)
							{
								Doctor* docfind = doctors.findbyid(userid);
								if (docfind != nullptr)
								{
									bool comparison1 = true;
									const char* correctpass1 = docfind->getPass();
									int i = 0;
									while (userpass[i] != '\0' && correctpass1[i] != '\0')
									{
										if (userpass[i] != correctpass1[i])
										{
											comparison1 = false;
											break;
										}
										i++;
									}
									if (userpass[i] != '\0' || correctpass1[i] != '\0')
									{
										comparison1 = false;
									}
									//printing initials of next state doctor window 
									if (comparison1 == true)
									{
										Doctorcurrent = docfind;
										char greeting1[100] = "WELCOME, DR. ";
										int gindex1 = 13;
										const char* docname = docfind->getName();
										for (int k = 0;docname[k] != '\0';k++)
										{
											greeting1[gindex1] = docname[k];
											gindex1++;
										}
										greeting1[gindex1] = '\0';
										doctortext.setString(greeting1);

										doctortexts.setString(docfind->getspecialization());
										correct = true;
										State = 2;




									}

								}
							}


							//admin credentials check
							else if (rolelogin == 3)
							{
								if (admin != nullptr && admin->getId() == userid)
								{
									bool comparison2 = true;
									const char* correctpass2 = admin->getPass();
									int i = 0;
									while (userpass[i] != '\0' && correctpass2[i] != '\0')
									{
										if (userpass[i] != correctpass2[i])
										{
											comparison2 = false;
											break;
										}
										i++;
									}
									if (userpass[i] != '\0' || correctpass2[i] != '\0')
									{
										comparison2 = false;
									}
									//admin next window initials
									if (comparison2 == true)
									{


										correct = true;
										State = 3;




									}

								}
							}



							//if wrong credentials then add in security log file
							if (correct == false)
							{
								LoginAttempts++;
								//write after 3 failed attempts
								if (LoginAttempts > 2)
								{
									ofstream securitylogfile("security_log.txt", ios::app);
									if (securitylogfile)
									{
										time_t now = time(0);
										char storetime[50];
										tm* ltime = localtime(&now);
										strftime(storetime, 50, "%d-%m-%Y %H:%M:%S:", ltime);
										const char* hold = "Unknown";
										if (rolelogin == 1)
										{
											hold = "Patient";
										}
										else if (rolelogin == 2)
										{
											hold = "Doctor";
										}
										else if (rolelogin == 3)
										{
											hold = "Admin";
										}
										securitylogfile << storetime << "," << hold << "," << userid << "," << "Failed" << "\n";
										securitylogfile.close();

									}
									enter17text.setString("Approach Admin. Account is locked");
									sf::sleep(sf::milliseconds(500));
									State = 0;

								}
								//if less than 3 attempts give another chance
								else
								{
									enter17text.setString("Invalid ID or Password, Try Again!!");
									idrectangle.cleartext();
									passrectangle.cleartext();
								}




							}



						}
					}



					//patient click handling button 1 and input validations
					else if (State == 11)
					{

						//checking for typing in the boxes
						if (bookspecbox11.getGlobalBounds().contains(mousePosition))
						{
							bookspecbox11.setstatus(true);
							bookdocbox11.setstatus(false);
							bookdatebox11.setstatus(false);
							bookslotbox11.setstatus(false);
						}
						else if (bookdocbox11.getGlobalBounds().contains(mousePosition))
						{
							bookspecbox11.setstatus(false);
							bookdocbox11.setstatus(true);
							bookdatebox11.setstatus(false);
							bookslotbox11.setstatus(false);
						}
						else if (bookdatebox11.getGlobalBounds().contains(mousePosition))
						{
							bookspecbox11.setstatus(false);
							bookdocbox11.setstatus(false);
							bookdatebox11.setstatus(true);
							bookslotbox11.setstatus(false);
						}
						else if (bookslotbox11.getGlobalBounds().contains(mousePosition))
						{
							bookspecbox11.setstatus(false);
							bookdocbox11.setstatus(false);
							bookdatebox11.setstatus(false);
							bookslotbox11.setstatus(true);
						}

						//after book button clicked verify if every thing entered is correct
						else if (bookbutton11.getGlobalBounds().contains(mousePosition))
						{
							const char* spec = bookspecbox11.getvalue();
							int         docid = atoi(bookdocbox11.getvalue());
							const char* date = bookdatebox11.getvalue();
							const char* slot = bookslotbox11.getvalue();

							//check if any field is empty
							if (spec[0] == '\0' || slot[0] == '\0' || date[0] == '\0' ||
								bookdocbox11.getvalue()[0] == '\0')
							{
								resulttext11.setFillColor(sf::Color::Red);
								resulttext11.setString("Please fill all fields.");
							}
							else
							{


								// check if specialization exists and display corresponding doctors

								Doctor** alldocs11 = doctors.getall();
								int dcount11 = doctors.getsize();
								Doctor* chosenDoc = nullptr;

								for (int d = 0; d < dcount11; d++)
								{
									if (alldocs11[d]->getId() == docid)
									{
										// validating specialization without case sensitivity

										const char* ds = alldocs11[d]->getspecialization();
										bool match = true;
										int si = 0;
										while (spec[si] != '\0' && ds[si] != '\0')
										{
											//conerting all to small case
											char c1 = spec[si];
											char c2 = ds[si];
											if (c1 >= 'A' && c1 <= 'Z')
											{
												c1 += 32;
											}
											if (c2 >= 'A' && c2 <= 'Z')
											{
												c2 += 32;
											}
											if (c1 != c2)
											{
												match = false;
												break;
											}
											si++;
										}
										//check if length is not same so false 

										if (spec[si] != '\0' || ds[si] != '\0')
										{
											match = false;
										}
										//doctor found
										if (match == true)
										{
											chosenDoc = alldocs11[d];
											break;
										}
									}
								}


								//error message
								if (chosenDoc == nullptr)
								{
									resulttext11.setFillColor(sf::Color::Red);
									resulttext11.setString("Doctor not found.");
								}
								//now checking date
								else
								{

									int dd = 0, mm = 0, yy = 0;
									//converting string date into integres of day,month,year
									dd = (date[0] - '0') * 10 + (date[1] - '0');

									mm = (date[3] - '0') * 10 + (date[4] - '0');

									yy = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
										(date[8] - '0') * 10 + (date[9] - '0');


									//error messages
									if (!Validator::validatedate(dd, mm, yy))
									{
										resulttext11.setFillColor(sf::Color::Red);
										resulttext11.setString("Invalid date.");
									}
									else if (!Validator::validatetimeslot(slot))
									{
										resulttext11.setFillColor(sf::Color::Red);
										resulttext11.setString("Invalid time slot.");
									}
									//correct inputs
									else
									{
										// now check slot not already taken
										bool slottaken = false;
										Appointment** allapps11 = appointments.getall();
										int acount11 = appointments.getsize();

										for (int a = 0; a < acount11; a++)
										{
											if (allapps11[a]->getdocid() == docid &&
												Appointment::Comparechars(allapps11[a]->getdate(), date) &&
												Appointment::Comparechars(allapps11[a]->getslot(), slot) &&
												!Appointment::Comparechars(allapps11[a]->getstatus(), "cancelled"))
											{
												slottaken = true;
												break;
											}
										}


										//error message
										if (slottaken == true)
										{
											resulttext11.setFillColor(sf::Color::Red);
											resulttext11.setString("Slot already taken. Choose another.");
										}
										//balance check error
										else if (Patientcurrent->getbalance() < chosenDoc->getfee())
										{
											resulttext11.setFillColor(sf::Color::Red);
											resulttext11.setString("Insufficient balance.");
										}

										//all correct now make changes accordingly
										else
										{
											// deduct fee from patient wallet
											*Patientcurrent -= chosenDoc->getfee();

											// generating new appointment ID, taking the next availabe id in numerical order
											int newappid11 = 0;
											for (int a = 0; a < acount11; a++)
											{
												if (allapps11[a]->getid() > newappid11)
												{
													newappid11 = allapps11[a]->getid();
												}
											}
											newappid11++;

											// generating new bill ID
											Bill** allbills11 = bills.getall();
											int bcount3 = bills.getsize();
											int newbillid = 0;
											for (int b = 0; b < bcount3; b++)
											{
												if (allbills11[b]->getid() > newbillid)
												{
													newbillid = allbills11[b]->getid();
												}
											}
											newbillid++;

											// getting today date for bill using predefined functions
											time_t tnow = time(0);//gives seconds after 1 jan 1970
											tm* tloc = localtime(&tnow);//converts seconds to day,month,year
											char todaystr[11];
											strftime(todaystr, 11, "%d-%m-%Y", tloc);//formatter

											// create appointment object and add to storage
											Appointment* newapp = new Appointment(
												newappid11,
												Patientcurrent->getId(),
												docid,
												date, slot, "pending");
											appointments.Add(newapp);


											// building appointment  line
											char appline11[200];
											int ali11 = 0;


											int newid11 = newappid11;
											char temparr11[20] = { 0 };
											int temppos11 = 0;


											if (newid11 == 0)
											{
												temparr11[temppos11++] = '0';
											}
											else
											{
												char temparr112[20];
												int temppos112 = 0;
												while (newid11 > 0)
												{
													temparr112[temppos112++] = newid11 % 10 + '0';
													newid11 = newid11 / 10;
												}
												while (temppos112 > 0)
												{
													temparr11[temppos11++] = temparr112[--temppos112];
												}

											}
											temparr11[temppos11] = '\0';




											for (int x = 0;temparr11[x] != '\0';x++)
											{
												appline11[ali11++] = temparr11[x];
											}
											appline11[ali11++] = ',';


											int newpatid11 = Patientcurrent->getId();
											char temppatarr11[20] = { 0 };
											int temppatpos11 = 0;


											if (newpatid11 == 0)
											{
												temppatarr11[temppatpos11++] = '0';
											}
											else
											{
												char temppatarr112[20];
												int temppatpos112 = 0;
												while (newpatid11 > 0)
												{
													temppatarr112[temppatpos112++] = newpatid11 % 10 + '0';
													newpatid11 = newpatid11 / 10;
												}
												while (temppatpos112 > 0)
												{
													temppatarr11[temppatpos11++] = temppatarr112[--temppatpos112];
												}

											}
											temppatarr11[temppatpos11] = '\0';


											for (int x = 0;temppatarr11[x] != '\0';x++)
											{
												appline11[ali11++] = temppatarr11[x];
											}
											appline11[ali11++] = ',';

											int newdocid11 = docid;
											char tempdocarr11[20] = { 0 };
											int tempdocpos11 = 0;


											if (newdocid11 == 0)
											{
												tempdocarr11[tempdocpos11++] = '0';
											}
											else
											{
												char tempdocarr112[20];
												int tempdocpos112 = 0;
												while (newdocid11 > 0)
												{
													tempdocarr112[tempdocpos112++] = newdocid11 % 10 + '0';
													newdocid11 = newdocid11 / 10;
												}
												while (tempdocpos112 > 0)
												{
													tempdocarr11[tempdocpos11++] = tempdocarr112[--tempdocpos112];
												}

											}
											tempdocarr11[tempdocpos11] = '\0';


											for (int x = 0;tempdocarr11[x] != '\0';x++)
											{
												appline11[ali11++] = tempdocarr11[x];
											}
											appline11[ali11++] = ',';


											for (int x = 0;date[x] != '\0';x++)
											{
												appline11[ali11++] = date[x];
											}
											appline11[ali11++] = ',';
											for (int x = 0;slot[x] != '\0';x++)
											{
												appline11[ali11++] = slot[x];
											}
											appline11[ali11++] = ',';

											const char* p11 = "pending";

											for (int x = 0;p11[x] != '\0';x++)
											{
												appline11[ali11++] = p11[x];
											}
											appline11[ali11] = '\0';

											//appending appointment file
											FileHandler::appendrecord("appointments.txt", appline11);

											// create bill and add to storage
											Bill* newbill11 = new Bill(
												newbillid,
												Patientcurrent->getId(),
												newappid11,
												chosenDoc->getfee(),
												"unpaid",
												todaystr);
											bills.Add(newbill11);

											// building bill line
											char billline11[200];
											int bli11 = 0;


											int newbillsid11 = newbillid;
											char tempbillsarr11[20] = { 0 };
											int tempbillspos11 = 0;


											if (newbillsid11 == 0)
											{
												tempbillsarr11[tempbillspos11++] = '0';
											}
											else
											{
												char tempbillsarr112[20];
												int tempbillspos112 = 0;
												while (newbillsid11 > 0)
												{
													tempbillsarr112[tempbillspos112++] = newbillsid11 % 10 + '0';
													newbillsid11 = newbillsid11 / 10;
												}
												while (tempbillspos112 > 0)
												{
													tempbillsarr11[tempbillspos11++] = tempbillsarr112[--tempbillspos112];
												}

											}
											tempbillsarr11[tempbillspos11] = '\0';

											for (int x = 0;tempbillsarr11[x] != '\0';x++)
											{
												billline11[bli11++] = tempbillsarr11[x];
											}
											billline11[bli11++] = ',';


											int newpatbillsid11 = Patientcurrent->getId();
											char temppatbillsarr11[20] = { 0 };
											int temppatbillspos11 = 0;


											if (newpatbillsid11 == 0)
											{
												temppatbillsarr11[temppatbillspos11++] = '0';
											}
											else
											{
												char temppatbillsarr112[20];
												int temppatbillspos112 = 0;
												while (newpatbillsid11 > 0)
												{
													temppatbillsarr112[temppatbillspos112++] = newpatbillsid11 % 10 + '0';
													newpatbillsid11 = newpatbillsid11 / 10;
												}
												while (temppatbillspos112 > 0)
												{
													temppatbillsarr11[temppatbillspos11++] = temppatbillsarr112[--temppatbillspos112];
												}

											}
											temppatbillsarr11[temppatbillspos11] = '\0';

											for (int x = 0;temppatbillsarr11[x] != '\0';x++)
											{
												billline11[bli11++] = temppatbillsarr11[x];
											}
											billline11[bli11++] = ',';



											int newappbillsid11 = newappid11;
											char tempappbillsarr11[20] = { 0 };
											int tempappbillspos11 = 0;


											if (newappbillsid11 == 0)
											{
												tempappbillsarr11[tempappbillspos11++] = '0';
											}
											else
											{
												char tempappbillsarr112[20];
												int tempappbillspos112 = 0;
												while (newappbillsid11 > 0)
												{
													tempappbillsarr112[tempappbillspos112++] = newappbillsid11 % 10 + '0';
													newappbillsid11 = newappbillsid11 / 10;
												}
												while (tempappbillspos112 > 0)
												{
													tempappbillsarr11[tempappbillspos11++] = tempappbillsarr112[--tempappbillspos112];
												}

											}
											tempappbillsarr11[tempappbillspos11] = '\0';

											for (int x = 0;tempappbillsarr11[x] != '\0';x++)
											{
												billline11[bli11++] = tempappbillsarr11[x];
											}
											billline11[bli11++] = ',';
											//converting float fees to string 
											float fv = chosenDoc->getfee();

											int fint = (int)fv;

											char ftmp[10];
											int fti = 0;
											char fstr[20];
											int fsi = 0;

											if (fint == 0)
											{
												fstr[fsi++] = '0';
											}
											else
											{
												while (fint > 0)
												{
													ftmp[fti++] = '0' + fint % 10;
													fint = fint / 10;
												}
												for (int x = fti - 1;x >= 0;x--)
												{
													fstr[fsi++] = ftmp[x];
												}
											}
											fstr[fsi++] = '.';
											fstr[fsi++] = '0';
											fstr[fsi++] = '0';
											fstr[fsi] = '\0';

											for (int x = 0;fstr[x] != '\0';x++)
											{
												billline11[bli11++] = fstr[x];
											}
											billline11[bli11++] = ',';

											const char* u11 = "unpaid";
											for (int x = 0;u11[x] != '\0';x++)
											{
												billline11[bli11++] = u11[x];
											}
											billline11[bli11++] = ',';

											for (int x = 0;todaystr[x] != '\0';x++)
											{
												billline11[bli11++] = todaystr[x];
											}
											billline11[bli11] = '\0';
											//appending bill file

											FileHandler::appendrecord("bills.txt", billline11);

											// update patient balance in file
											char patline4[300];
											int ni4 = 0;

											int newpatbalaid11 = Patientcurrent->getId();
											char temppatbalaarr11[20] = { 0 };
											int temppatbalapos11 = 0;


											if (newpatbalaid11 == 0)
											{
												temppatbalaarr11[temppatbalapos11++] = '0';
											}
											else
											{
												char temppatbalaarr112[20];
												int temppatbalapos112 = 0;
												while (newpatbalaid11 > 0)
												{
													temppatbalaarr112[temppatbalapos112++] = newpatbalaid11 % 10 + '0';
													newpatbalaid11 = newpatbalaid11 / 10;
												}
												while (temppatbalapos112 > 0)
												{
													temppatbalaarr11[temppatbalapos11++] = temppatbalaarr112[--temppatbalapos112];
												}

											}

											temppatbalaarr11[temppatbalapos11] = '\0';




											for (int x = 0;temppatbalaarr11[x] != '\0';x++)
											{

												patline4[ni4++] = temppatbalaarr11[x];
											}
											patline4[ni4++] = ',';

											const char* nm1111 = Patientcurrent->getName();

											for (int x = 0;nm1111[x] != '\0';x++)
											{
												patline4[ni4++] = nm1111[x];
											}
											patline4[ni4++] = ',';

											int agev4 = Patientcurrent->getage();

											char agetmp4[5];
											int ati7 = 0;
											char agestr4[5];
											int asi7 = 0;

											if (agev4 == 0)
											{
												agestr4[asi7++] = '0';
											}
											else
											{
												while (agev4 > 0)
												{
													agetmp4[ati7++] = '0' + agev4 % 10;
													agev4 /= 10;
												}
												for (int x = ati7 - 1;x >= 0;x--)
												{
													agestr4[asi7++] = agetmp4[x];
												}
											}
											agestr4[asi7] = '\0';

											for (int x = 0;agestr4[x] != '\0';x++)
											{
												patline4[ni4++] = agestr4[x];
											}
											patline4[ni4++] = ',';

											patline4[ni4++] = Patientcurrent->getgender();
											patline4[ni4++] = ',';

											const char* con4 = Patientcurrent->getcontact();
											for (int x = 0;con4[x] != '\0';x++)
											{
												patline4[ni4++] = con4[x];
											}
											patline4[ni4++] = ',';

											const char* pw4 = Patientcurrent->getPass();
											for (int x = 0;pw4[x] != '\0';x++)
											{
												patline4[ni4++] = pw4[x];
											}
											patline4[ni4++] = ',';

											float bal4 = Patientcurrent->getbalance();
											int balint4 = (int)bal4;
											char baltmp4[10];
											int bti5 = 0;
											char balstr4[20];
											int bsi5 = 0;

											if (balint4 == 0)
											{
												balstr4[bsi5++] = '0';
											}
											else
											{
												while (balint4 > 0)
												{
													baltmp4[bti5++] = '0' + balint4 % 10;
													balint4 /= 10;
												}
												for (int x = bti5 - 1;x >= 0;x--)
												{
													balstr4[bsi5++] = baltmp4[x];
												}
											}
											balstr4[bsi5] = '\0';

											for (int x = 0;balstr4[x] != '\0';x++)
											{
												patline4[ni4++] = balstr4[x];
											}
											patline4[ni4] = '\0';

											//record modified for patient
											FileHandler::modifyrecord("patients.txt",
												Patientcurrent->getId(), patline4);

											// update balance display
											char patbalance4[100] = "BALANCE: PKR ";

											int newval4 = 13;

											for (int x = 0;balstr4[x] != '\0';x++)
											{


												patbalance4[newval4++] = balstr4[x];
											}
											patbalance4[newval4] = '\0';


											patienttexts.setString(patbalance4);

											resulttext11.setFillColor(sf::Color::Green);
											resulttext11.setString("Appointment booked successfully!");
											bookspecbox11.cleartext();
											bookdocbox11.cleartext();
											bookdatebox11.cleartext();
											bookslotbox11.cleartext();

										}
									}
								}
							}
						}
					}

					//click handling for state 12 and validations

					else if (State == 12)
					{
						//writing in cancel box
						if (cancelbox12.getGlobalBounds().contains(mousePosition))
						{
							cancelbox12.setstatus(true);
						}
						//changing things after pressing cancel button

						else if (cancelbutton12.getGlobalBounds().contains(mousePosition))
						{
							int appid = atoi(cancelbox12.getvalue());
							bool found = false;

							Appointment** allapps12 = appointments.getall();
							int acount12 = appointments.getsize();


							for (int i = 0; i < acount12; i++)
							{
								//checks if appointment exists and not completed yet
								if (allapps12[i]->getid() == appid &&
									allapps12[i]->getpatid() == Patientcurrent->getId() &&
									Appointment::Comparechars(allapps12[i]->getstatus(), "pending"))
								{
									found = true;

									// find doctor fee for refund of patient
									float fee = 0;
									Doctor** alldocs12 = doctors.getall();
									int dcount12 = doctors.getsize();
									for (int d = 0; d < dcount12; d++)
									{
										if (alldocs12[d]->getId() == allapps12[i]->getdocid())
										{
											fee = alldocs12[d]->getfee();
											break;
										}
									}

									// refund using +=
									*Patientcurrent += fee;

									// update appointment status
									allapps12[i]->setstatus("cancelled");

									// build appointment  line
									char appline12[200];
									int ai12 = 0;

									int av = allapps12[i]->getid();
									char atmp[10];
									int ati4 = 0;
									char astr2[10];
									int asi4 = 0;

									if (av == 0)

									{
										astr2[asi4++] = '0';
									}
									else
									{
										while (av > 0)
										{
											atmp[ati4++] = '0' + av % 10;
											av = av / 10;
										}

										for (int x = ati4 - 1; x >= 0; x--)
										{
											astr2[asi4++] = atmp[x];
										}
									}
										astr2[asi4] = '\0';

										for (int x = 0; astr2[x] != '\0'; x++)
										{
											appline12[ai12++] = astr2[x];
										}
										appline12[ai12++] = ',';

										int pv = allapps12[i]->getpatid();

										char ptmp2[10];
										int pti2 = 0;
										char pstr2[10];
										int psi2 = 0;

										if (pv == 0)
										{
											pstr2[psi2++] = '0';
										}
										else
										{
											while (pv > 0)
											{
												ptmp2[pti2++] = '0' + pv % 10;
												pv /= 10;
											}
											for (int x = pti2 - 1; x >= 0; x--)
											{
												pstr2[psi2++] = ptmp2[x];
											}

										}
										pstr2[psi2] = '\0';
										for (int x = 0; pstr2[x] != '\0'; x++)
										{
											appline12[ai12++] = pstr2[x];
										}
										appline12[ai12++] = ',';

										int dv = allapps12[i]->getdocid();

										char dtmp[10];
										int dti = 0;
										char dstr[10];
										int dsi = 0;

										if (dv == 0)
										{
											dstr[dsi++] = '0';
										}
										else
										{
											while (dv > 0)
											{
												dtmp[dti++] = '0' + dv % 10;
												dv /= 10;
											}
											for (int x = dti - 1; x >= 0; x--)
											{
												dstr[dsi++] = dtmp[x];
											}

										}
										dstr[dsi] = '\0';

										for (int x = 0; dstr[x] != '\0'; x++)
										{
											appline12[ai12++] = dstr[x];
										}
										appline12[ai12++] = ',';

										const char* dt2 = allapps12[i]->getdate();
										for (int x = 0; dt2[x] != '\0'; x++)
										{
											appline12[ai12++] = dt2[x];
										}
										appline12[ai12++] = ',';

										const char* sl = allapps12[i]->getslot();
										for (int x = 0; sl[x] != '\0'; x++)
										{
											appline12[ai12++] = sl[x];
										}
										appline12[ai12++] = ',';

										const char* cancelled = "cancelled";
										for (int x = 0; cancelled[x] != '\0'; x++)
										{
											appline12[ai12++] = cancelled[x];
										}
										appline12[ai12] = '\0';
										//modify appointment line from pending to cancel

										FileHandler::modifyrecord("appointments.txt",
											allapps12[i]->getid(), appline12);


										// update bill status to cancelled

										Bill** allbills12 = bills.getall();
										int bcount12 = bills.getsize();

										for (int b = 0; b < bcount12; b++)
										{

											if (allbills12[b]->getappid() == appid)
											{
												allbills12[b]->setstatus("cancelled");

												char billline2[200];
												int bi2 = 0;

												int biv2 = allbills12[b]->getid();
												char btmp2[10];
												int bti3 = 0;
												char bstr2[10];
												int bsi3 = 0;

												if (biv2 == 0)
												{
													bstr2[bsi3++] = '0';
												}
												else
												{
													while (biv2 > 0)
													{
														btmp2[bti3++] = '0' + biv2 % 10;
														biv2 /= 10;
													}
													for (int x = bti3 - 1; x >= 0; x--)
													{
														bstr2[bsi3++] = btmp2[x];
													}

												}
												bstr2[bsi3] = '\0';
												for (int x = 0; bstr2[x] != '\0'; x++)
												{
													billline2[bi2++] = bstr2[x];
												}
												billline2[bi2++] = ',';

												int piv2 = allbills12[b]->getpatid();
												char ptmp3[10];
												int pti3 = 0;
												char pstr3[10];
												int psi3 = 0;

												if (piv2 == 0)
												{
													pstr3[psi3++] = '0';
												}
												else
												{
													while (piv2 > 0)
													{
														ptmp3[pti3++] = '0' + piv2 % 10;
														piv2 /= 10;
													}
													for (int x = pti3 - 1; x >= 0; x--)
													{
														pstr3[psi3++] = ptmp3[x];
													}
												}
												pstr3[psi3] = '\0';
												for (int x = 0; pstr3[x] != '\0'; x++)
												{
													billline2[bi2++] = pstr3[x];
												}
												billline2[bi2++] = ',';

												int aiv2 = allbills12[b]->getappid();
												char atmp2[10];
												int ati5 = 0;
												char astr3[10];
												int asi5 = 0;

												if (aiv2 == 0)
												{
													astr3[asi5++] = '0';
												}
												else
												{
													while (aiv2 > 0)
													{
														atmp2[ati5++] = '0' + aiv2 % 10;
														aiv2 /= 10;
													}
													for (int x = ati5 - 1; x >= 0; x--)
													{
														astr3[asi5++] = atmp2[x];
													}
												}

												astr3[asi5] = '\0';
												for (int x = 0; astr3[x] != '\0'; x++)
												{
													billline2[bi2++] = astr3[x];
												}
												billline2[bi2++] = ',';

												float amtv2 = allbills12[b]->getamount();
												int amtint2 = (int)amtv2;
												char amttmp2[10];
												int amtti2 = 0;
												char amtstr2[20];
												int amtsi2 = 0;

												if (amtint2 == 0)
												{
													amtstr2[amtsi2++] = '0';
												}
												else
												{
													while (amtint2 > 0)
													{
														amttmp2[amtti2++] = '0' + amtint2 % 10;
														amtint2 /= 10;
													}
													for (int x = amtti2 - 1; x >= 0; x--)
													{
														amtstr2[amtsi2++] = amttmp2[x];
													}
												}
												amtstr2[amtsi2++] = '.'; amtstr2[amtsi2++] = '0';
												amtstr2[amtsi2++] = '0';
												amtstr2[amtsi2] = '\0';
												for (int x = 0; amtstr2[x] != '\0'; x++)
												{
													billline2[bi2++] = amtstr2[x];
												}
												billline2[bi2++] = ',';

												const char* cs = "cancelled";
												for (int x = 0; cs[x] != '\0'; x++)
												{
													billline2[bi2++] = cs[x];
												}
												billline2[bi2++] = ',';

												const char* bd = allbills12[b]->getdate();
												for (int x = 0; bd[x] != '\0'; x++)
												{
													billline2[bi2++] = bd[x];
												}
												billline2[bi2] = '\0';

												FileHandler::modifyrecord("bills.txt",
													allbills12[b]->getid(), billline2);
												break;
											}
										}

										// updating patient balance in file
										char patline3[300];
										int ni3 = 0;

										int idv3 = Patientcurrent->getId();
										char idtmp3[10];
										int iti3 = 0;
										char idstr3[10];
										int isi3 = 0;

										if (idv3 == 0)
										{
											idstr3[isi3++] = '0';
										}
										else
										{
											while (idv3 > 0)
											{
												idtmp3[iti3++] = '0' + idv3 % 10;
												idv3 /= 10;
											} for (int x = iti3 - 1; x >= 0; x--)
											{
												idstr3[isi3++] = idtmp3[x];
											}
										}
										idstr3[isi3] = '\0';

										for (int x = 0; idstr3[x] != '\0'; x++)
										{
											patline3[ni3++] = idstr3[x];
										}
										patline3[ni3++] = ',';

										const char* nm3 = Patientcurrent->getName();
										for (int x = 0; nm3[x] != '\0'; x++)
										{
											patline3[ni3++] = nm3[x];
										}
										patline3[ni3++] = ',';

										int agev3 = Patientcurrent->getage();

										char agetmp3[5];
										int ati6 = 0;
										char agestr3[5];
										int asi6 = 0;

										if (agev3 == 0)
										{
											agestr3[asi6++] = '0';
										}
										else
										{
											while (agev3 > 0)
											{
												agetmp3[ati6++] = '0' + agev3 % 10;
												agev3 /= 10;
											}
											for (int x = ati6 - 1; x >= 0; x--)
											{
												agestr3[asi6++] = agetmp3[x];
											}
										}
										agestr3[asi6] = '\0';

										for (int x = 0; agestr3[x] != '\0'; x++)
										{
											patline3[ni3++] = agestr3[x];
										}
										patline3[ni3++] = ',';

										patline3[ni3++] = Patientcurrent->getgender();
										patline3[ni3++] = ',';

										const char* con3 = Patientcurrent->getcontact();
										for (int x = 0; con3[x] != '\0'; x++)
										{
											patline3[ni3++] = con3[x];
										}
										patline3[ni3++] = ',';

										const char* pw3 = Patientcurrent->getPass();
										for (int x = 0; pw3[x] != '\0'; x++)
										{
											patline3[ni3++] = pw3[x];
										}
										patline3[ni3++] = ',';

										float bal3 = Patientcurrent->getbalance();
										int balint3 = (int)bal3;
										char baltmp3[10];
										int bti4 = 0;
										char balstr3[20];
										int bsi4 = 0;

										if (balint3 == 0)
										{
											balstr3[bsi4++] = '0';
										}
										else
										{
											while (balint3 > 0)
											{
												baltmp3[bti4++] = '0' + balint3 % 10;
												balint3 /= 10;
											}
											for (int x = bti4 - 1; x >= 0; x--)
											{
												balstr3[bsi4++] = baltmp3[x];
											}
										}
										balstr3[bsi4] = '\0';

										for (int x = 0; balstr3[x] != '\0'; x++)
										{
											patline3[ni3++] = balstr3[x];
										}
										patline3[ni3] = '\0';
										//modifying patient file
										FileHandler::modifyrecord("patients.txt",
											Patientcurrent->getId(), patline3);


										// update balance display
										char patbalance12[100] = "BALANCE: PKR ";
										int newval3 = 13;

										for (int x = 0; balstr3[x] != '\0'; x++)
										{

											patbalance12[newval3++] = balstr3[x];
										}
										patbalance12[newval3] = '\0';

										patienttexts.setString(patbalance12);

										resulttext12.setFillColor(sf::Color::Green);
										resulttext12.setString("Appointment cancelled. Fee refunded.");
										cancelbox12.cleartext();
										cancelbox12.setstatus(false);
										break;
								}
							}
								//error message
								if (!found)
								{
									resulttext12.setFillColor(sf::Color::Red);
									resulttext12.setString("Invalid appointment ID.");
								}
						}
					}


						//no click handling needed as they only display output no buttons and boxes
						else if (State == 13)
						{
							//
						}
						else if (State == 14)
						{
							//
						}
						else if (State == 15)
						{
							//
						}

						//click handling for state 16

						else if (State == 16)
						{
							if (paybillbox16.getGlobalBounds().contains(mousePosition))
							{
								paybillbox16.setstatus(true);
							}

							else if (paybillbutton16.getGlobalBounds().contains(mousePosition))
							{
								int billid16 = atoi(paybillbox16.getvalue());
								bool found = false;

								Bill** allbills16 = bills.getall();
								int bcount16 = bills.getsize();

								for (int i = 0; i < bcount16; i++)
								{
									if (allbills16[i]->getid() == billid16 &&
										allbills16[i]->getpatid() == Patientcurrent->getId())
									{
										// checking status is unpaid
										bool isunpaid = Appointment::Comparechars(
											allbills16[i]->getstatus(), "unpaid");

										if (!isunpaid)
										{
											resulttext16.setFillColor(sf::Color::Red);
											resulttext16.setString("Bill is not unpaid.");
											found = true;
											break;
										}

										// checking balance
										if (Patientcurrent->getbalance() < allbills16[i]->getamount())
										{
											resulttext16.setFillColor(sf::Color::Red);
											resulttext16.setString("Insufficient balance.");
											found = true;
											break;
										}

										// deduct balance
										*Patientcurrent -= allbills16[i]->getamount();

										// update bill status
										allbills16[i]->setstatus("paid");

										// build bill line
										char billline16[200];
										int bi16 = 0;

										// adding bill_id
										int biv = allbills16[i]->getid();
										char btmp[10];
										int bti = 0;
										char bstr[10];
										int bsi = 0;
										if (biv == 0)
										{
											bstr[bsi++] = '0';
										}
										else
										{
											while (biv > 0)
											{
												btmp[bti++] = '0' + biv % 10;
												biv /= 10;
											}
											for (int x = bti - 1; x >= 0; x--)
											{
												bstr[bsi++] = btmp[x];
											}
										}
										bstr[bsi] = '\0';
										for (int x = 0; bstr[x] != '\0'; x++)
										{
											billline16[bi16++] = bstr[x];
										}
										billline16[bi16++] = ',';

										// adding patient_id
										int piv = allbills16[i]->getpatid();
										char ptmp[10];
										int pti = 0;
										char pstr[10];
										int psi = 0;
										if (piv == 0)
										{
											pstr[psi++] = '0';
										}
										else
										{
											while (piv > 0)
											{
												ptmp[pti++] = '0' + piv % 10;
												piv /= 10;
											}
											for (int x = pti - 1; x >= 0; x--)
											{
												pstr[psi++] = ptmp[x];
											}
										}
										pstr[psi] = '\0';

										for (int x = 0; pstr[x] != '\0'; x++)
										{
											billline16[bi16++] = pstr[x];
										}
										billline16[bi16++] = ',';

										// adding appointment_id
										int aiv = allbills16[i]->getappid();
										char atmp[10];
										int ati2 = 0;
										char astr[10];
										int asi2 = 0;
										if (aiv == 0)
										{
											astr[asi2++] = '0';
										}

										else
										{
											while (aiv > 0)
											{
												atmp[ati2++] = '0' + aiv % 10;
												aiv /= 10;
											} for (int x = ati2 - 1; x >= 0; x--)
											{
												astr[asi2++] = atmp[x];
											}
										}
										astr[asi2] = '\0';
										for (int x = 0; astr[x] != '\0'; x++)
										{
											billline16[bi16++] = astr[x];
										}
										billline16[bi16++] = ',';

										// adding amount
										float amtv = allbills16[i]->getamount();
										int amtint = (int)amtv;
										char amttmp[10];
										int amtti = 0;
										char amtstr[20];
										int amtsi = 0;
										if (amtint == 0)
										{
											amtstr[amtsi++] = '0';
										}
										else
										{
											while (amtint > 0)
											{
												amttmp[amtti++] = '0' + amtint % 10;
												amtint /= 10;
											}
											for (int x = amtti - 1; x >= 0; x--)
											{
												amtstr[amtsi++] = amttmp[x];
											}
										}
										amtstr[amtsi++] = '.';
										amtstr[amtsi++] = '0';
										amtstr[amtsi++] = '0';

										amtstr[amtsi] = '\0';
										for (int x = 0; amtstr[x] != '\0'; x++)
										{
											billline16[bi16++] = amtstr[x];
										}
										billline16[bi16++] = ',';

										// adding status
										const char* st = "paid";

										for (int x = 0; st[x] != '\0'; x++)
										{
											billline16[bi16++] = st[x];
										}
										billline16[bi16++] = ',';

										// adding date
										const char* dt = allbills16[i]->getdate();
										for (int x = 0; dt[x] != '\0'; x++)
										{
											billline16[bi16++] = dt[x];
										}
										billline16[bi16] = '\0';
										//modifying bills file
										FileHandler::modifyrecord("bills.txt",
											allbills16[i]->getid(), billline16);

										// updating patient balance in file
										char patline16[300];
										int ni = 0;

										int idv2 = Patientcurrent->getId();
										char idtmp2[10];
										int iti2 = 0;
										char idstr2[10];
										int isi2 = 0;

										if (idv2 == 0)
										{
											idstr2[isi2++] = '0';
										}

										else
										{
											while (idv2 > 0)
											{
												idtmp2[iti2++] = '0' + idv2 % 10;
												idv2 /= 10;
											}
											for (int x = iti2 - 1; x >= 0; x--)
											{
												idstr2[isi2++] = idtmp2[x];
											}
										}
										idstr2[isi2] = '\0';
										for (int x = 0; idstr2[x] != '\0'; x++)
										{
											patline16[ni++] = idstr2[x];
										}
										patline16[ni++] = ',';

										const char* nm2 = Patientcurrent->getName();
										for (int x = 0; nm2[x] != '\0'; x++)
										{
											patline16[ni++] = nm2[x];
										}
										patline16[ni++] = ',';

										int agev2 = Patientcurrent->getage();

										char agetmp2[5];
										int ati3 = 0;
										char agestr2[5];
										int asi3 = 0;
										if (agev2 == 0)
										{
											agestr2[asi3++] = '0';
										}
										else
										{
											while (agev2 > 0)
											{
												agetmp2[ati3++] = '0' + agev2 % 10;
												agev2 /= 10;
											}
											for (int x = ati3 - 1; x >= 0; x--)
											{
												agestr2[asi3++] = agetmp2[x];
											}
										}
										agestr2[asi3] = '\0';

										for (int x = 0; agestr2[x] != '\0'; x++)
										{
											patline16[ni++] = agestr2[x];
										}
										patline16[ni++] = ',';

										patline16[ni++] = Patientcurrent->getgender();
										patline16[ni++] = ',';

										const char* con2 = Patientcurrent->getcontact();
										for (int x = 0; con2[x] != '\0'; x++)
										{
											patline16[ni++] = con2[x];
										}
										patline16[ni++] = ',';

										const char* pw2 = Patientcurrent->getPass();
										for (int x = 0; pw2[x] != '\0'; x++)
										{
											patline16[ni++] = pw2[x];
										}
										patline16[ni++] = ',';

										float bal2 = Patientcurrent->getbalance();
										int balint2 = (int)bal2;
										char baltmp2[10];
										int bti2 = 0;
										char balstr2[20];
										int bsi2 = 0;

										if (balint2 == 0)
										{
											balstr2[bsi2++] = '0';
										}

										else
										{
											while (balint2 > 0)
											{
												baltmp2[bti2++] = '0' + balint2 % 10;
												balint2 /= 10;
											}
											for (int x = bti2 - 1; x >= 0; x--)
											{

												balstr2[bsi2++] = baltmp2[x];
											}
										}
										balstr2[bsi2] = '\0';

										for (int x = 0; balstr2[x] != '\0'; x++)
										{
											patline16[ni++] = balstr2[x];
										}
										patline16[ni] = '\0';

										//modifying patients file
										FileHandler::modifyrecord("patients.txt",
											Patientcurrent->getId(), patline16);

										// updating balance display
										char patbalance2[100] = "BALANCE: PKR ";
										int newval2 = 13;

										for (int x = 0; balstr2[x] != '\0'; x++)
										{

											patbalance2[newval2++] = balstr2[x];
										}
										patbalance2[newval2] = '\0';

										patienttexts.setString(patbalance2);

										resulttext16.setFillColor(sf::Color::Green);
										resulttext16.setString("Bill paid successfully!");
										paybillbox16.cleartext();
										paybillbox16.setstatus(false);
										found = true;
										break;
									}
								}

								//error message
								if (!found)
								{
									resulttext16.setFillColor(sf::Color::Red);
									resulttext16.setString("Bill ID not found or does not belong to you.");
								}
						    }
					    }
				
						//click handling for state 17

						else if (State == 17)
						{
							if (topupbox17.getGlobalBounds().contains(mousePosition))
							{
								topupbox17.setstatus(true);
							}
							//changes after clicking top up button

							else if (topupbutton17.getGlobalBounds().contains(mousePosition))
							{

								float amount = atof(topupbox17.getvalue());
								if (amount <= 0)
								{
									resulttext17.setFillColor(sf::Color::Red);
									resulttext17.setString("Invalid amount. Must be greater than 0.");
								}

								else
								{
									*Patientcurrent += amount;

									// build new line
									char newline17[300];
									int ni17 = 0;

									// adding id
									int idv = Patientcurrent->getId();
									char idtmp[10];
									int iti = 0;
									char idstr[10];
									int isi = 0;
									if (idv == 0)
									{
										idstr[isi++] = '0';
									}
									else
									{
										while (idv > 0)
										{
											idtmp[iti++] = '0' + idv % 10;
											idv /= 10;
										}
										for (int x = iti - 1; x >= 0; x--)
										{
											idstr[isi++] = idtmp[x];
										}
									}
									idstr[isi] = '\0';
									for (int x = 0; idstr[x] != '\0'; x++)
									{
										newline17[ni17++] = idstr[x];
									}
									newline17[ni17++] = ',';

									// adding name
									const char* nm = Patientcurrent->getName();
									for (int x = 0; nm[x] != '\0'; x++)
									{
										newline17[ni17++] = nm[x];
									}
									newline17[ni17++] = ',';

									// adding age
									int agev = Patientcurrent->getage();
									char agetmp[5];
									int ati = 0;
									char agestr[5];
									int asi = 0;

									if (agev == 0)
									{
										agestr[asi++] = '0';
									}
									else
									{
										while (agev > 0)
										{
											agetmp[ati++] = '0' + agev % 10;
											agev /= 10;
										}
										for (int x = ati - 1; x >= 0; x--)
										{
											agestr[asi++] = agetmp[x];
										}
										agestr[asi] = '\0';
									
										for (int x = 0; agestr[x] != '\0'; x++)
										{
											newline17[ni17++] = agestr[x];
										}
										newline17[ni17++] = ',';

										// adding gender
										newline17[ni17++] = Patientcurrent->getgender();
										newline17[ni17++] = ',';

										// adding contact
										const char* con = Patientcurrent->getcontact();
										for (int x = 0; con[x] != '\0'; x++)
										{
											newline17[ni17++] = con[x];
										}
										newline17[ni17++] = ',';

										//adding password
										const char* pw = Patientcurrent->getPass();
										for (int x = 0; pw[x] != '\0'; x++)
										{
											newline17[ni17++] = pw[x];
										}
										newline17[ni17++] = ',';

										// adding balance
										float bal = Patientcurrent->getbalance();
										int balint = (int)bal;
										char baltmp[10];
										int bti = 0;
										char balstr[20];
										int bsi = 0;
										if (balint == 0)
										{
											balstr[bsi++] = '0';
										}
										else
										{
											while (balint > 0)
											{
												baltmp[bti++] = '0' + balint % 10;
												balint /= 10;
											}
											for (int x = bti - 1; x >= 0; x--)
											{
												balstr[bsi++] = baltmp[x];
											}

										}
										balstr[bsi] = '\0';
										for (int x = 0; balstr[x] != '\0'; x++)
										{
											newline17[ni17++] = balstr[x];
										}
										newline17[ni17] = '\0';

										//modifying patients file
										FileHandler::modifyrecord("patients.txt",
											Patientcurrent->getId(), newline17);

										// updating balance display
										char patbalance[100] = "BALANCE: PKR ";
										int newval = 13;
										for (int x = 0; balstr[x] != '\0'; x++)
										{

											patbalance[newval++] = balstr[x];
										}
										patbalance[newval] = '\0';

										patienttexts.setString(patbalance);

										resulttext17.setFillColor(sf::Color::Green);
										resulttext17.setString("Balance updated successfully!");
										topupbox17.cleartext();
										topupbox17.setstatus(false);
								    }
							    }
						    }
					    }
							//only display
							else if (State == 21)
							{

							}

							else if (State == 22)
							{
								if (markcompletebox22.getGlobalBounds().contains(mousePosition))
								{
									markcompletebox22.setstatus(true);
								}

								else if (markcompletebutton22.getGlobalBounds().contains(mousePosition))
								{
									int appid = atoi(markcompletebox22.getvalue());
									bool found = false;

									// getting today date
									time_t tnow2 = time(0);
									tm* tloc2 = localtime(&tnow2);
									char todaystr2[11];
									strftime(todaystr2, 11, "%d-%m-%Y", tloc2);

									Appointment** allapps22 = appointments.getall();
									int acount12 = appointments.getsize();

									for (int a = 0; a < acount12; a++)
									{
										//if appointment was pending we mark it complete
										if (allapps22[a]->getid() == appid &&
											allapps22[a]->getdocid() == Doctorcurrent->getId() &&
											Appointment::Comparechars(allapps22[a]->getstatus(), "pending") &&
											Appointment::Comparechars(allapps22[a]->getdate(), todaystr2))
										{
											found = true;
											allapps22[a]->setstatus("completed");

											// build appointment  line
											char appline22[200];
											int ali22 = 0;


											int newappid22 = allapps22[a]->getid();
											char tempapparr22[20] = { 0 };
											int tempapppos22 = 0;


											if (newappid22 == 0)
											{
												tempapparr22[tempapppos22++] = '0';
											}
											else
											{
												char tempapparr222[20];
												int tempapppos222 = 0;
												while (newappid22 > 0)
												{
													tempapparr222[tempapppos222++] = newappid22 % 10 + '0';
													newappid22 = newappid22 / 10;
												}
												while (tempapppos222 > 0)
												{
													tempapparr22[tempapppos22++] = tempapparr222[--tempapppos222];
												}

											}
											tempapparr22[tempapppos22] = '\0';



											for (int x = 0;tempapparr22[x] != '\0';x++)
											{
												appline22[ali22++] = tempapparr22[x];
											}
											appline22[ali22++] = ',';


											int newpatid22 = allapps22[a]->getpatid();
											char temppatarr22[20] = { 0 };
											int temppatpos22 = 0;


											if (newpatid22 == 0)
											{
												temppatarr22[temppatpos22++] = '0';
											}
											else
											{
												char temppatarr222[20];
												int temppatpos222 = 0;
												while (newpatid22 > 0)
												{
													temppatarr222[temppatpos222++] = newpatid22 % 10 + '0';
													newpatid22 = newpatid22 / 10;
												}
												while (temppatpos222 > 0)
												{
													temppatarr22[temppatpos22++] = temppatarr222[--temppatpos222];
												}

											}
											temppatarr22[temppatpos22] = '\0';

											for (int x = 0;temppatarr22[x] != '\0';x++)
											{
												appline22[ali22++] = temppatarr22[x];
											}
											appline22[ali22++] = ',';

											int newdocid22 = allapps22[a]->getdocid();
											char tempdocarr22[20] = { 0 };
											int tempdocpos22 = 0;


											if (newdocid22 == 0)
											{
												tempdocarr22[tempdocpos22++] = '0';
											}
											else
											{
												char tempdocarr222[20];
												int tempdocpos222 = 0;
												while (newdocid22 > 0)
												{
													tempdocarr222[tempdocpos222++] = newdocid22 % 10 + '0';
													newdocid22 = newdocid22 / 10;
												}
												while (tempdocpos222 > 0)
												{
													tempdocarr22[tempdocpos22++] = tempdocarr222[--tempdocpos222];
												}

											}
											tempdocarr22[tempdocpos22] = '\0';


											for (int x = 0;tempdocarr22[x] != '\0';x++)
											{
												appline22[ali22++] = tempdocarr22[x];
											}
											appline22[ali22++] = ',';


											const char* dt7 = allapps22[a]->getdate();
											for (int x = 0;dt7[x] != '\0';x++)
											{
												appline22[ali22++] = dt7[x];
											}
											appline22[ali22++] = ',';

											const char* sl4 = allapps22[a]->getslot();
											for (int x = 0;sl4[x] != '\0';x++)
											{
												appline22[ali22++] = sl4[x];
											}
											appline22[ali22++] = ',';

											const char* comp = "completed";
											for (int x = 0;comp[x] != '\0';x++)
											{
												appline22[ali22++] = comp[x];
											}
											appline22[ali22] = '\0';
											//modifying appointments file
											FileHandler::modifyrecord("appointments.txt",
												allapps22[a]->getid(), appline22);

											docresulttext22.setFillColor(sf::Color::Green);
											docresulttext22.setString("Appointment marked as completed.");
											markcompletebox22.cleartext();
											markcompletebox22.setstatus(false);
											break;
										}
									}
									//error message
									if (!found)
									{
										docresulttext22.setFillColor(sf::Color::Red);
										docresulttext22.setString("Invalid appointment ID.");
									}
								}
							}

							else if (State == 23)
							{
								if (marknoshowbox23.getGlobalBounds().contains(mousePosition))
								{
									marknoshowbox23.setstatus(true);
								}
								else if (marknoshbutton23.getGlobalBounds().contains(mousePosition))
								{
									int appid2 = atoi(marknoshowbox23.getvalue());
									bool found2 = false;

									time_t tnow3 = time(0);
									tm* tloc3 = localtime(&tnow3);
									char todaystr3[11];
									strftime(todaystr3, 11, "%d-%m-%Y", tloc3);

									Appointment** allapps23 = appointments.getall();
									int acount23 = appointments.getsize();

									for (int a = 0; a < acount23; a++)
									{
										//changing status from pending to no-show
										if (allapps23[a]->getid() == appid2 &&
											allapps23[a]->getdocid() == Doctorcurrent->getId() &&
											Appointment::Comparechars(allapps23[a]->getstatus(), "pending") &&
											Appointment::Comparechars(allapps23[a]->getdate(), todaystr3))
										{
											found2 = true;
											allapps23[a]->setstatus("no-show");

											// build appointment line
											char appline23[200];
											int ali23 = 0;

											int newappid23 = allapps23[a]->getid();
											char tempapparr23[20] = { 0 };
											int tempapppos23 = 0;


											if (newappid23 == 0)
											{
												tempapparr23[tempapppos23++] = '0';
											}
											else
											{
												char tempapparr232[20];
												int tempapppos232 = 0;
												while (newappid23 > 0)
												{
													tempapparr232[tempapppos232++] = newappid23 % 10 + '0';
													newappid23 = newappid23 / 10;
												}
												while (tempapppos232 > 0)
												{
													tempapparr23[tempapppos23++] = tempapparr232[--tempapppos232];
												}

											}
											tempapparr23[tempapppos23] = '\0';



											for (int x = 0;tempapparr23[x] != '\0';x++)
											{
												appline23[ali23++] = tempapparr23[x];
											}
											appline23[ali23++] = ',';


											int newpatid23 = allapps23[a]->getpatid();
											char temppatarr23[20] = { 0 };
											int temppatpos23 = 0;


											if (newpatid23 == 0)
											{
												temppatarr23[temppatpos23++] = '0';
											}
											else
											{
												char temppatarr232[20];
												int temppatpos232 = 0;
												while (newpatid23 > 0)
												{
													temppatarr232[temppatpos232++] = newpatid23 % 10 + '0';
													newpatid23 = newpatid23 / 10;
												}
												while (temppatpos232 > 0)
												{
													temppatarr23[temppatpos23++] = temppatarr232[--temppatpos232];
												}

											}
											temppatarr23[temppatpos23] = '\0';

											for (int x = 0;temppatarr23[x] != '\0';x++)
											{
												appline23[ali23++] = temppatarr23[x];
											}
											appline23[ali23++] = ',';

											int newdocid23 = allapps23[a]->getdocid();
											char tempdocarr23[20] = { 0 };
											int tempdocpos23 = 0;


											if (newdocid23 == 0)
											{
												tempdocarr23[tempdocpos23++] = '0';
											}
											else
											{
												char tempdocarr232[20];
												int tempdocpos232 = 0;
												while (newdocid23 > 0)
												{
													tempdocarr232[tempdocpos232++] = newdocid23 % 10 + '0';
													newdocid23 = newdocid23 / 10;
												}
												while (tempdocpos232 > 0)
												{
													tempdocarr23[tempdocpos23++] = tempdocarr232[--tempdocpos232];
												}

											}
											tempdocarr23[tempdocpos23] = '\0';


											for (int x = 0;tempdocarr23[x] != '\0';x++)
											{
												appline23[ali23++] = tempdocarr23[x];
											}
											appline23[ali23++] = ',';








											const char* dt8 = allapps23[a]->getdate();
											for (int x = 0;dt8[x] != '\0';x++)
											{
												appline23[ali23++] = dt8[x];
											}
											appline23[ali23++] = ',';

											const char* sl5 = allapps23[a]->getslot();
											for (int x = 0;sl5[x] != '\0';x++)
											{
												appline23[ali23++] = sl5[x];
											}
											appline23[ali23++] = ',';

											const char* nsh = "no-show";
											for (int x = 0;nsh[x] != '\0';x++)
											{
												appline23[ali23++] = nsh[x];
											}
											appline23[ali23] = '\0';

											FileHandler::modifyrecord("appointments.txt",
												allapps23[a]->getid(), appline23);

											// updating bill to cancelled
											Bill** allbills23 = bills.getall();
											int bcount23 = bills.getsize();
											for (int b = 0; b < bcount23; b++)
											{
												if (allbills23[b]->getappid() == appid2)
												{
													allbills23[b]->setstatus("cancelled");

													char billsline23[200];
													int bli23 = 0;

													int newbillsid23 = allbills23[b]->getid();
													char tempbillsarr23[20] = { 0 };
													int tempbillspos23 = 0;


													if (newbillsid23 == 0)
													{
														tempbillsarr23[tempbillspos23++] = '0';
													}
													else
													{
														char tempbillsarr232[20];
														int tempbillspos232 = 0;
														while (newbillsid23 > 0)
														{
															tempbillsarr232[tempbillspos232++] = newbillsid23 % 10 + '0';
															newbillsid23 = newbillsid23 / 10;
														}
														while (tempbillspos232 > 0)
														{
															tempbillsarr23[tempbillspos23++] = tempbillsarr232[--tempbillspos232];
														}

													}
													tempbillsarr23[tempbillspos23] = '\0';



													for (int x = 0;tempbillsarr23[x] != '\0';x++)
													{
														billsline23[ali23++] = tempbillsarr23[x];
													}
													billsline23[bli23++] = ',';


													int newpatid23 = allbills23[b]->getpatid();
													char temppatarr23[20] = { 0 };
													int temppatpos23 = 0;


													if (newpatid23 == 0)
													{
														temppatarr23[temppatpos23++] = '0';
													}
													else
													{
														char temppatarr232[20];
														int temppatpos232 = 0;
														while (newpatid23 > 0)
														{
															temppatarr232[temppatpos232++] = newpatid23 % 10 + '0';
															newpatid23 = newpatid23 / 10;
														}
														while (temppatpos232 > 0)
														{
															temppatarr23[temppatpos23++] = temppatarr232[--temppatpos232];
														}

													}
													temppatarr23[temppatpos23] = '\0';

													for (int x = 0;temppatarr23[x] != '\0';x++)
													{
														billsline23[ali23++] = temppatarr23[x];
													}
													billsline23[ali23++] = ',';

													int newdocid23 = allbills23[b]->getappid();
													char tempdocarr23[20] = { 0 };
													int tempdocpos23 = 0;


													if (newdocid23 == 0)
													{
														tempdocarr23[tempdocpos23++] = '0';
													}
													else
													{
														char tempdocarr232[20];
														int tempdocpos232 = 0;
														while (newdocid23 > 0)
														{
															tempdocarr232[tempdocpos232++] = newdocid23 % 10 + '0';
															newdocid23 = newdocid23 / 10;
														}
														while (tempdocpos232 > 0)
														{
															tempdocarr23[tempdocpos23++] = tempdocarr232[--tempdocpos232];
														}

													}
													tempdocarr23[tempdocpos23] = '\0';


													for (int x = 0;tempdocarr23[x] != '\0';x++)
													{
														billsline23[ali23++] = tempdocarr23[x];
													}
													billsline23[ali23++] = ',';







													float amtv4 = allbills23[b]->getamount();
													int amtint4 = (int)amtv4;
													char amttmp4[10];
													int amtti4 = 0;
													char amtstr4[20];
													int amtsi4 = 0;
													if (amtint4 == 0)
													{
														amtstr4[amtsi4++] = '0';
													}
													else
													{
														while (amtint4 > 0)
														{
															amttmp4[amtti4++] = '0' + amtint4 % 10;
															amtint4 /= 10;
														}
														for (int x = amtti4 - 1;x >= 0;x--)
														{
															amtstr4[amtsi4++] = amttmp4[x];
														}
													}
													amtstr4[amtsi4++] = '.';
													amtstr4[amtsi4++] = '0';
													amtstr4[amtsi4++] = '0';
													amtstr4[amtsi4] = '\0';
													for (int x = 0;amtstr4[x] != '\0';x++)
													{
														billsline23[bli23++] = amtstr4[x];
													}
													billsline23[bli23++] = ',';

													const char* cs2 = "cancelled";
													for (int x = 0;cs2[x] != '\0';x++)
													{
														billsline23[bli23++] = cs2[x];
													}
													billsline23[bli23++] = ',';

													const char* bd2 = allbills23[b]->getdate();
													for (int x = 0;bd2[x] != '\0';x++)
													{
														billsline23[bli23++] = bd2[x];
													}
													billsline23[bli23] = '\0';
													//modifying bills file
													FileHandler::modifyrecord("bills.txt",
														allbills23[b]->getid(), billsline23);
													break;
												}
											}

											docresulttext23.setFillColor(sf::Color::Yellow);
											docresulttext23.setString("Appointment marked as no-show.");
											marknoshowbox23.cleartext();
											marknoshowbox23.setstatus(false);
											break;
										}
									}
									//error message
									if (!found2)
									{
										docresulttext23.setFillColor(sf::Color::Red);
										docresulttext23.setString("Invalid appointment ID.");
									}
								}
							}

							else if (State == 24)
							{
								if (prescappbox24.getGlobalBounds().contains(mousePosition))
								{
									prescappbox24.setstatus(true);
									prescmedbox24.setstatus(false);
									prescnotesbox24.setstatus(false);
								}
								else if (prescmedbox24.getGlobalBounds().contains(mousePosition))
								{
									prescappbox24.setstatus(false);
									prescmedbox24.setstatus(true);
									prescnotesbox24.setstatus(false);
								}
								else if (prescnotesbox24.getGlobalBounds().contains(mousePosition))
								{
									prescappbox24.setstatus(false);
									prescmedbox24.setstatus(false);
									prescnotesbox24.setstatus(true);
								}


								else if (prescbutton24.getGlobalBounds().contains(mousePosition))
								{
									int appid3 = atoi(prescappbox24.getvalue());
									const char* medicines = prescmedbox24.getvalue();
									const char* notes = prescnotesbox24.getvalue();

									// validating appointment belongs to doctor and is completed
									bool appvalid = false;
									const char* appdate = nullptr;
									Appointment** allapps24 = appointments.getall();
									int acount24 = appointments.getsize();

									for (int a = 0; a < acount24; a++)
									{
										if (allapps24[a]->getid() == appid3 &&
											allapps24[a]->getdocid() == Doctorcurrent->getId() &&
											Appointment::Comparechars(allapps24[a]->getstatus(), "completed"))
										{
											appvalid = true;
											appdate = allapps24[a]->getdate();

											// checking prescription not already written
											Prescription** allpres2 = prescriptions.getall();
											int pcount2 = prescriptions.getsize();
											bool alreadywritten = false;
											for (int p = 0; p < pcount2; p++)
											{
												if (allpres2[p]->getappointmentid() == appid3)
												{
													alreadywritten = true;
													break;
												}
											}

											if (alreadywritten)
											{
												docresulttext24.setFillColor(sf::Color::Red);
												docresulttext24.setString("Prescription already written.");
												break;
											}

											// generating new prescription ID
											int newpresid = 0;
											for (int p = 0; p < pcount2; p++)
												if (allpres2[p]->getid() > newpresid)
													newpresid = allpres2[p]->getid();
											newpresid++;

											int patid4 = allapps24[a]->getpatid();

											// creating prescription object
											Prescription* newpres = new Prescription(
												newpresid, appid3, patid4,
												Doctorcurrent->getId(),
												appdate, medicines, notes);
											prescriptions.Add(newpres);

											// build prescription  line
											char presline24[1000];
											int pli24 = 0;


											int newbillsid23 = newpresid;
											char tempbillsarr23[20] = { 0 };
											int tempbillspos23 = 0;


											if (newbillsid23 == 0)
											{
												tempbillsarr23[tempbillspos23++] = '0';
											}
											else
											{
												char tempbillsarr232[20];
												int tempbillspos232 = 0;
												while (newbillsid23 > 0)
												{
													tempbillsarr232[tempbillspos232++] = newbillsid23 % 10 + '0';
													newbillsid23 = newbillsid23 / 10;
												}
												while (tempbillspos232 > 0)
												{
													tempbillsarr23[tempbillspos23++] = tempbillsarr232[--tempbillspos232];
												}

											}
											tempbillsarr23[tempbillspos23] = '\0';



											for (int x = 0;tempbillsarr23[x] != '\0';x++)
											{
												presline24[pli24++] = tempbillsarr23[x];
											}
											presline24[pli24++] = ',';


											int newpatid23 = appid3;
											char temppatarr23[20] = { 0 };
											int temppatpos23 = 0;


											if (newpatid23 == 0)
											{
												temppatarr23[temppatpos23++] = '0';
											}
											else
											{
												char temppatarr232[20];
												int temppatpos232 = 0;
												while (newpatid23 > 0)
												{
													temppatarr232[temppatpos232++] = newpatid23 % 10 + '0';
													newpatid23 = newpatid23 / 10;
												}
												while (temppatpos232 > 0)
												{
													temppatarr23[temppatpos23++] = temppatarr232[--temppatpos232];
												}

											}
											temppatarr23[temppatpos23] = '\0';

											for (int x = 0;temppatarr23[x] != '\0';x++)
											{
												presline24[pli24++] = temppatarr23[x];
											}
											presline24[pli24++] = ',';

											int newdocid23 = patid4;
											char tempdocarr23[20] = { 0 };
											int tempdocpos23 = 0;


											if (newdocid23 == 0)
											{
												tempdocarr23[tempdocpos23++] = '0';
											}
											else
											{
												char tempdocarr232[20];
												int tempdocpos232 = 0;
												while (newdocid23 > 0)
												{
													tempdocarr232[tempdocpos232++] = newdocid23 % 10 + '0';
													newdocid23 = newdocid23 / 10;
												}
												while (tempdocpos232 > 0)
												{
													tempdocarr23[tempdocpos23++] = tempdocarr232[--tempdocpos232];
												}

											}
											tempdocarr23[tempdocpos23] = '\0';


											for (int x = 0;tempdocarr23[x] != '\0';x++)
											{
												presline24[pli24++] = tempdocarr23[x];
											}
											presline24[pli24++] = ',';

											int snewdocid23 = Doctorcurrent->getId();
											char stempdocarr23[20] = { 0 };
											int stempdocpos23 = 0;


											if (snewdocid23 == 0)
											{
												stempdocarr23[stempdocpos23++] = '0';
											}
											else
											{
												char stempdocarr232[20];
												int stempdocpos232 = 0;
												while (snewdocid23 > 0)
												{
													stempdocarr232[stempdocpos232++] = snewdocid23 % 10 + '0';
													snewdocid23 = snewdocid23 / 10;
												}
												while (stempdocpos232 > 0)
												{
													stempdocarr23[stempdocpos23++] = stempdocarr232[--stempdocpos232];
												}

											}
											stempdocarr23[stempdocpos23] = '\0';


											for (int x = 0;tempdocarr23[x] != '\0';x++)
											{
												presline24[pli24++] = tempdocarr23[x];
											}
											presline24[pli24++] = ',';


											for (int x = 0;appdate[x] != '\0';x++)
											{
												presline24[pli24++] = appdate[x];
											}
											presline24[pli24++] = ',';

											for (int x = 0;medicines[x] != '\0';x++)
											{
												presline24[pli24++] = medicines[x];
											}
											presline24[pli24++] = ',';

											for (int x = 0;notes[x] != '\0';x++)
											{
												presline24[pli24++] = notes[x];
											}
											presline24[pli24] = '\0';
											//appending prescriptions file

											FileHandler::appendrecord("prescriptions.txt", presline24);

											docresulttext24.setFillColor(sf::Color::Green);
											docresulttext24.setString("Prescription saved.");
											prescappbox24.cleartext();
											prescmedbox24.cleartext();
											prescnotesbox24.cleartext();
											break;

										}
									}
									//error message
									if (!appvalid)
									{
										docresulttext24.setFillColor(sf::Color::Red);
										docresulttext24.setString("Invalid appointment ID.");
									}
								}
							}

							else if (State == 25)
							{
								if (pathistorybox25.getGlobalBounds().contains(mousePosition))
								{
									pathistorybox25.setstatus(true);
								}
								else if (historybutton25.getGlobalBounds().contains(mousePosition))
								{
									int patid5 = atoi(pathistorybox25.getvalue());

									// validate patient exists and has completed appointment with this doctor
									bool hasaccess = false;
									Appointment** allapps8 = appointments.getall();
									int acount8 = appointments.getsize();

									for (int a = 0; a < acount8; a++)
									{
										if (allapps8[a]->getpatid() == patid5 &&
											allapps8[a]->getdocid() == Doctorcurrent->getId() &&
											Appointment::Comparechars(allapps8[a]->getstatus(), "completed"))
										{
											hasaccess = true;
											break;
										}
									}
									//error message
									if (!hasaccess)
									{
										historyresult25.setString("Access denied. You can only view records of your own patients.");
									}
									else
									{
										// building prescription history
										char histstr[1000];
										int hli = 0;
										Prescription** allpres25 = prescriptions.getall();
										int pcount25 = prescriptions.getsize();

										for (int p = 0; p < pcount25; p++)
										{
											if (allpres25[p]->getpatientid() == patid5 &&
												allpres25[p]->getdoctorid() == Doctorcurrent->getId())
											{
												const char* dt9 = allpres25[p]->getdate();
												for (int x = 0;dt9[x] != '\0';x++)
												{
													histstr[hli++] = dt9[x];
												}
												histstr[hli++] = ' ';

												const char* med2 = allpres25[p]->getmedicines();
												for (int x = 0;med2[x] != '\0';x++)
												{
													histstr[hli++] = med2[x];
												}
												histstr[hli++] = '\n';

												const char* nt2 = allpres25[p]->getnotes();
												for (int x = 0;nt2[x] != '\0';x++)
												{
													histstr[hli++] = nt2[x];
												}
												histstr[hli++] = '\n';
												histstr[hli++] = '\n';
											}
										}
										histstr[hli] = '\0';
										historyresult25.setString(hli > 0 ? histstr : "No records found.");
									}
								}
							}

							// click handling admin buttons and boxes
							else if (State == 31)
							{
								if (docnamebox31.getGlobalBounds().contains(mousePosition))
								{
									docnamebox31.setstatus(true);
									docspecbox31.setstatus(false);
									doccontbox31.setstatus(false);
									docpassbox31.setstatus(false);
									docfeebox31.setstatus(false);
								}
								else if (docspecbox31.getGlobalBounds().contains(mousePosition))
								{
									docnamebox31.setstatus(false);
									docspecbox31.setstatus(true);
									doccontbox31.setstatus(false);
									docpassbox31.setstatus(false);
									docfeebox31.setstatus(false);
								}
								else if (doccontbox31.getGlobalBounds().contains(mousePosition))
								{
									docnamebox31.setstatus(false);
									docspecbox31.setstatus(false);
									doccontbox31.setstatus(true);
									docpassbox31.setstatus(false);
									docfeebox31.setstatus(false);
								}
								else if (docpassbox31.getGlobalBounds().contains(mousePosition))
								{
									docnamebox31.setstatus(false);
									docspecbox31.setstatus(false);
									doccontbox31.setstatus(false);
									docpassbox31.setstatus(true);
									docfeebox31.setstatus(false);
								}
								else if (docfeebox31.getGlobalBounds().contains(mousePosition))
								{
									docnamebox31.setstatus(false);
									docspecbox31.setstatus(false);
									doccontbox31.setstatus(false);
									docpassbox31.setstatus(false);
									docfeebox31.setstatus(true);
								}
								//doing things after add doctor button is clicked
								else if (addDocbutton.getGlobalBounds().contains(mousePosition))
								{
									const char* dname31 = docnamebox31.getvalue();
									const char* dspec31 = docspecbox31.getvalue();
									const char* dcon31 = doccontbox31.getvalue();
									const char* dpass31 = docpassbox31.getvalue();
									float       dfee31 = atof(docfeebox31.getvalue());

									//error message
									if (!Validator::validatecontact(dcon31))
									{
										adminresulttext371.setFillColor(sf::Color::Red);
										adminresulttext371.setString("Invalid contact. Must be 11 digits.");
									}
									else if (!Validator::validatepassword(dpass31))
									{
										adminresulttext371.setFillColor(sf::Color::Red);
										adminresulttext371.setString("Password must be minimum 6 characters");
									}
									else if (!Validator::validateconsultationfee(dfee31))
									{
										adminresulttext371.setFillColor(sf::Color::Red);
										adminresulttext371.setString("Invalid fee. Must be positive.");
									}
									else
									{
										//if correct credentials add doctor to required files
										int newdocid31 = 0;
										Doctor** docarray31 = doctors.getall();
										int dcount31 = doctors.getsize();

										for (int d = 0; d < dcount31; d++)
										{
											if (docarray31[d]->getId() > newdocid31)
											{
												newdocid31 = docarray31[d]->getId();
											}
										}
										newdocid31++;

										Doctor* newdoc31 = new Doctor(newdocid31, dname31, dspec31, dcon31, dpass31, dfee31);
										doctors.Add(newdoc31);


										char docline31[300];
										int dli31 = 0;


										int tempVal31 = newdocid31;
										char temparr31[10] = { 0 };
										int temppos31 = 0;

										if (tempVal31 == 0)
										{
											temparr31[temppos31++] = '0';
										}
										else
										{
											char temparr311[10];
											int temppos311 = 0;
											while (tempVal31 > 0)
											{
												temparr311[temppos311++] = (tempVal31 % 10) + '0';
												tempVal31 = tempVal31 / 10;
											}
											while (temppos311 > 0)
											{
												temparr31[temppos31++] = temparr311[--temppos311];
											}
										}
										temparr31[temppos31] = '\0';

										for (int x = 0; temparr31[x] != '\0'; x++)
										{
											docline31[dli31++] = temparr31[x];
										}
										docline31[dli31++] = ',';



										for (int x = 0;dname31[x] != '\0';x++)
										{
											docline31[dli31++] = dname31[x];
										}
										docline31[dli31++] = ',';

										for (int x = 0;dspec31[x] != '\0';x++)
										{
											docline31[dli31++] = dspec31[x];
										}
										docline31[dli31++] = ',';

										for (int x = 0;dcon31[x] != '\0';x++)
										{
											docline31[dli31++] = dcon31[x];
										}
										docline31[dli31++] = ',';

										for (int x = 0;dpass31[x] != '\0';x++)
										{
											docline31[dli31++] = dpass31[x];
										}
										docline31[dli31++] = ',';



										int fint31 = (int)dfee31;

										char feetemp31[10];
										int fti31 = 0;
										char feearray31[20];
										int feepos31 = 0;
										if (fint31 == 0)
										{
											feearray31[feepos31++] = '0';
										}
										else
										{
											while (fint31 > 0)
											{
												feetemp31[fti31++] = '0' + fint31 % 10;
												fint31 = fint31 / 10;
											}
											for (int x = fti31 - 1;x >= 0;x--)
											{
												feearray31[feepos31++] = feetemp31[x];
											}
										}
										feearray31[feepos31++] = '.';
										feearray31[feepos31++] = '0';
										feearray31[feepos31++] = '0';
										feearray31[feepos31] = '\0';
										for (int x = 0;feearray31[x] != '\0';x++)
										{
											docline31[dli31++] = feearray31[x];
										}
										docline31[dli31] = '\0';
										//appending doctor file
										FileHandler::appendrecord("doctors.txt", docline31);

										adminresulttext371.setFillColor(sf::Color::Green);


										char success31[50] = "Doctor added. ID: ";
										int si31 = 18;




										int newtempVal31 = newdocid31;
										char temparr2[10] = { 0 };
										int temppos2 = 0;

										if (newtempVal31 == 0)
										{
											temparr2[temppos2++] = '0';
										}
										else
										{
											char newtemparr311[10];
											int newtemppos311 = 0;
											while (newtempVal31 > 0)
											{
												newtemparr311[newtemppos311++] = (newtempVal31 % 10) + '0';
												newtempVal31 = newtempVal31 / 10;
											}
											while (newtemppos311 > 0)
											{
												temparr2[temppos2++] = newtemparr311[--newtemppos311];
											}
										}
										temparr2[temppos2] = '\0';

										for (int x = 0;temparr2[x] != '\0';x++)
										{
											success31[si31++] = temparr2[x];
										}
										success31[si31] = '\0';

										adminresulttext371.setString(success31);

										docnamebox31.cleartext();
										docspecbox31.cleartext();
										doccontbox31.cleartext();
										docpassbox31.cleartext();
										docfeebox31.cleartext();

									}
								}
							}
							else if (State == 32)
							{


								if (removedocbox32.getGlobalBounds().contains(mousePosition))
								{
									removedocbox32.setstatus(true);
								}
								else if (removedocbutton32.getGlobalBounds().contains(mousePosition))
								{
									int removeid32 = atoi(removedocbox32.getvalue());

									bool pending32 = false;

									Appointment** allapp32 = appointments.getall();
									int appcount32 = appointments.getsize();
									for (int a = 0; a < appcount32; a++)
									{
										if (allapp32[a]->getdocid() == removeid32 && Appointment::Comparechars(allapp32[a]->getstatus(), "pending"))
										{
											pending32 = true;
											break;
										}
									}

									if (pending32==true)
									{
										adminresulttext372.setFillColor(sf::Color::Red);
										adminresulttext372.setString("Can't remove. Doctor has pending appointments.");
									}
									else
									{

										Doctor* found32 = doctors.findbyid(removeid32);
										if (found32 == nullptr)
										{
											adminresulttext372.setFillColor(sf::Color::Red);
											adminresulttext372.setString("Doctor not found.");
										}
										else
										{
											delete found32;
											doctors.removebyid(removeid32);
											FileHandler::deleterecord("doctors.txt", removeid32);
											adminresulttext372.setFillColor(sf::Color::Green);
											adminresulttext372.setString("Doctor removed.");
											removedocbox32.cleartext();
										}
									}
								}
							}
							//only output display so no need for click handling logic
							else if (State == 33)
							{
								//
							}
							else if (State == 34)
							{
								//
							}
							else if (State == 35)
							{
								//
							}
							else if (State == 36)
							{
								//
							}
							else if (State == 37)
							{
								if (dischargebox37.getGlobalBounds().contains(mousePosition))
								{
									dischargebox37.setstatus(true);
								}
								else if (dischargebutton37.getGlobalBounds().contains(mousePosition))
								{
									int dischargeid37 = atoi(dischargebox37.getvalue());

									Patient* dischargepat37 = patients.findbyid(dischargeid37);

									if (dischargepat37 == nullptr)
									{
										adminresulttext377.setFillColor(sf::Color::Red);
										adminresulttext377.setString("Patient not found.");
									}
									else
									{
										//patient should not be discharged if he has pending bills
										bool unpaid37 = false;
										Bill** patbill37 = bills.getall();
										int billcount37 = bills.getsize();
										for (int b = 0; b < billcount37; b++)
										{
											if (patbill37[b]->getpatid() == dischargeid37 && Appointment::Comparechars(patbill37[b]->getstatus(), "unpaid"))
											{
												unpaid37 = true;
												break;
											}
										}

										if (unpaid37==true)
										{
											adminresulttext377.setFillColor(sf::Color::Red);
											adminresulttext377.setString("Cannot discharge. As Patient has unpaid bills.");
										}

										else
										{
											//check for pending appointments
											bool pending37 = false;
											Appointment** appointments37 = appointments.getall();
											int appcount37 = appointments.getsize();
											for (int a = 0; a < appcount37; a++)
											{
												if (appointments37[a]->getpatid() == dischargeid37 &&
													Appointment::Comparechars(appointments37[a]->getstatus(), "pending"))
												{
													pending37 = true;
													break;
												}

											}

											if (pending37==true)
											{
												adminresulttext377.setFillColor(sf::Color::Red);
												adminresulttext377.setString("Cannot discharge.As Patient has pending appointments.");
											}
											else
											{

												char dischargeline37[300];
												int dli37 = 0;


												int tempVal37 = dischargepat37->getId();
												char temparr37[10] = { 0 };
												int temppos37 = 0;

												if (tempVal37 == 0)
												{
													temparr37[temppos37++] = '0';
												}
												else
												{
													char temparr371[10];
													int temppos371 = 0;
													while (tempVal37 > 0)
													{
														temparr371[temppos371++] = (tempVal37 % 10) + '0';
														tempVal37 = tempVal37 / 10;
													}
													while (temppos371 > 0)
													{
														temparr37[temppos37++] = temparr371[--temppos371];
													}
												}
												temparr37[temppos37] = '\0';


												for (int x = 0;temparr37[x] != '\0';x++)
												{
													dischargeline37[dli37++] = temparr37[x];
												}
												dischargeline37[dli37++] = ',';

												const char* dnm = dischargepat37->getName();
												for (int x = 0;dnm[x] != '\0';x++)
												{
													dischargeline37[dli37++] = dnm[x];
												}
												dischargeline37[dli37++] = ',';

												int tempage37 = dischargepat37->getage();


												char tempagearr37[10] = { 0 };
												int tempagepos37 = 0;

												if (tempage37 == 0)
												{
													tempagearr37[tempagepos37++] = '0';
												}
												else
												{
													char temparr371[10];
													int temppos371 = 0;
													while (tempage37 > 0)
													{
														temparr371[temppos371++] = (tempage37 % 10) + '0';
														tempage37 = tempage37 / 10;
													}
													while (temppos371 > 0)
													{
														tempagearr37[tempagepos37++] = temparr371[--temppos371];
													}
												}
												tempagearr37[tempagepos37] = '\0';


												for (int x = 0;tempagearr37[x] != '\0';x++)
												{

													dischargeline37[dli37++] = tempagearr37[x];
												}
												dischargeline37[dli37++] = ',';

												dischargeline37[dli37++] = dischargepat37->getgender();
												dischargeline37[dli37++] = ',';

												const char* dcon2 = dischargepat37->getcontact();
												for (int x = 0;dcon2[x] != '\0';x++)
												{
													dischargeline37[dli37++] = dcon2[x];
												}
												dischargeline37[dli37++] = ',';

												const char* dpw = dischargepat37->getPass();

												for (int x = 0;dpw[x] != '\0';x++)
												{
													dischargeline37[dli37++] = dpw[x];
												}
												dischargeline37[dli37++] = ',';

												float dbal37 = dischargepat37->getbalance();

												int dbalint37 = (int)dbal37;

												char dbaltmp37[10];
												int dbti37 = 0;
												char dbalarr37[20];
												int dbsi37 = 0;
												if (dbalint37 == 0)
												{
													dbalarr37[dbsi37++] = '0';
												}
												else
												{
													while (dbalint37 > 0)
													{
														dbaltmp37[dbti37++] = '0' + dbalint37 % 10;
														dbalint37 /= 10;
													}
													for (int x = dbti37 - 1;x >= 0;x--)
													{
														dbalarr37[dbsi37++] = dbaltmp37[x];
													}
												}
												dbalarr37[dbsi37] = '\0';

												for (int x = 0;dbalarr37[x] != '\0';x++)
												{
													dischargeline37[dli37++] = dbalarr37[x];
												}
												dischargeline37[dli37] = '\0';

												//changes in all files due to discharging a patient
												FileHandler::appendrecord("discharged.txt", dischargeline37);

												//also delete record in existing files
												FileHandler::deleterecord("patients.txt", dischargeid37);
												FileHandler::deleterecord("appointments.txt", dischargeid37);
												FileHandler::deleterecord("bills.txt", dischargeid37);
												FileHandler::deleterecord("prescriptions.txt", dischargeid37);


												delete dischargepat37;
												patients.removebyid(dischargeid37);

												adminresulttext377.setFillColor(sf::Color::Green);
												adminresulttext377.setString("Patient discharged and archived successfully.");
												dischargebox37.cleartext();
											}
										}
									}
								}
							}
							//only display
							else if (State == 38)
							{
								//
							}
							else if (State == 39)
							{
								//
							}



					}










				}


			}




				//window clearning before drawing logic begins
				window.clear(sf::Color(127, 127, 127));




				//drawing logics
				//4 initial buttons
				if (State == 0)
				{
					window.draw(background_Sprite);
					window.draw(text);
					window.draw(texts);
					window.draw(button1);
					window.draw(button2);
					window.draw(button3);
					window.draw(button4);
					window.draw(text1);
					window.draw(text2);
					window.draw(text3);
					window.draw(text4);
				}
				//patint buttons
				else if (State == 1)
				{
					window.draw(background_Sprite1);
					window.draw(patienttext);
					window.draw(patienttexts);
					window.draw(patientbutton1);
					window.draw(patientbutton2);
					window.draw(patientbutton3);
					window.draw(patientbutton4);
					window.draw(patientbutton5);
					window.draw(patientbutton6);
					window.draw(patientbutton7);
					window.draw(patientbutton8);
					window.draw(patienttext1);
					window.draw(patienttext2);
					window.draw(patienttext3);
					window.draw(patienttext4);
					window.draw(patienttext5);
					window.draw(patienttext6);
					window.draw(patienttext7);
					window.draw(patienttext8);
				}
				//doctor buttons
				else if (State == 2)
				{
					window.draw(background_Sprite1);
					window.draw(doctortext);
					window.draw(doctortexts);
					window.draw(doctorbutton1);
					window.draw(doctorbutton2);
					window.draw(doctorbutton3);
					window.draw(doctorbutton4);
					window.draw(doctorbutton5);
					window.draw(doctorbutton6);
					window.draw(doctortext1);
					window.draw(doctortext2);
					window.draw(doctortext3);
					window.draw(doctortext4);
					window.draw(doctortext5);
					window.draw(doctortext6);
				}
				//admin buttons
				else if (State == 3)
				{
					window.draw(background_Sprite1);
					window.draw(Admintext);
					window.draw(Adminbutton1);
					window.draw(Adminbutton2);
					window.draw(Adminbutton3);
					window.draw(Adminbutton4);
					window.draw(Adminbutton5);
					window.draw(Adminbutton6);
					window.draw(Adminbutton7);
					window.draw(Adminbutton8);
					window.draw(Adminbutton9);
					window.draw(Adminbutton10);
					window.draw(Admintext1);
					window.draw(Admintext2);
					window.draw(Admintext3);
					window.draw(Admintext4);
					window.draw(Admintext5);
					window.draw(Admintext6);
					window.draw(Admintext7);
					window.draw(Admintext8);
					window.draw(Admintext9);
					window.draw(Admintext10);

				}
				//login screen display
				else if (State == 5)
				{
					window.draw(background_Sprite3);
					window.draw(logintext);
					window.draw(amount17text);
					window.draw(loginpassword);
					window.draw(buttonlogin);
					window.draw(loginclick);
					idrectangle.drawscreen(window);
					passrectangle.drawscreen(window);
					window.draw(enter17text);


				}
				//book appointment
				else if (State == 11)
				{

					window.draw(background_Sprite2);
					window.draw(bookspec11);
					window.draw(bookdocid11);
					window.draw(bookdate11);
					window.draw(bookslot11);
					window.draw(bookbutton11);
					window.draw(bookbuttontext11);
					bookspecbox11.drawscreen(window);
					bookdocbox11.drawscreen(window);
					bookdatebox11.drawscreen(window);
					bookslotbox11.drawscreen(window);

					// show the names and id's of doctors on basis of entered specialization for patient to view

					char docliststr[500];
					int dli = 0;
					Doctor** alldocs3 = doctors.getall();
					int dcount3 = doctors.getsize();
					const char* spec2 = bookspecbox11.getvalue();

					if (spec2[0] != '\0')
					{
						//match doctors with typed specialization
						for (int d = 0; d < dcount3; d++)
						{
							const char* ds2 = alldocs3[d]->getspecialization();
							bool match2 = true;
							int si2 = 0;
							while (spec2[si2] != '\0' && ds2[si2] != '\0')
							{
								char c1 = spec2[si2];
								char c2 = ds2[si2];
								if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
								if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
								if (c1 != c2) { match2 = false; break; }
								si2++;
							}
							if (spec2[si2] != '\0' || ds2[si2] != '\0')
							{
								match2 = false;
							}

							if (match2==true)
							{
								const char* dn = alldocs3[d]->getName();
								for (int x = 0; dn[x] != '\0'; x++)
								{
									docliststr[dli++] = dn[x];
								}
								docliststr[dli++] = ' ';
								docliststr[dli++] = '(';
								// add id
								int dv2 = alldocs3[d]->getId();

								char dtmp2[10];
								int dti2 = 0;
								char dstr2[10];
								int dsi2 = 0;

								if (dv2 == 0)
								{
									dstr2[dsi2++] = '0'; 
								}
								else 
								{
									while (dv2 > 0)
									{
										dtmp2[dti2++] = '0' + dv2 % 10;
										dv2 = dv2/10;
									}
									for (int x = dti2 - 1; x >= 0; x--)
									{
										dstr2[dsi2++] = dtmp2[x];
									}
								}
								dstr2[dsi2] = '\0';
								for (int x = 0; dstr2[x] != '\0'; x++)
								{
									docliststr[dli++] = dstr2[x];
								}
								docliststr[dli++] = ')';
								docliststr[dli++] = '\n';
							}
						}
					}

					docliststr[dli] = '\0';
					bookdoclistshow11.setString(docliststr);
					window.draw(bookdoclistshow11);
					window.draw(resulttext11);




				}
				//cancel appointment
				else if (State == 12)
				{

					window.draw(background_Sprite2);

					// showing pending appointments for this patient
					char pendingstr[800];
					int pli = 0;
					Appointment** allapps3 = appointments.getall();
					int acount3 = appointments.getsize();
					for (int a = 0; a < acount3; a++)
					{
						if (allapps3[a]->getpatid() == Patientcurrent->getId() &&
							Appointment::Comparechars(allapps3[a]->getstatus(), "pending"))
						{
							// add appointment id
							int av2 = allapps3[a]->getid();
							char atmp3[10];
							int ati8 = 0;
							char astr4[10];
							int asi8 = 0;

							if (av2 == 0)
							{
								astr4[asi8++] = '0'; 
							}
							else 
							{
								while (av2 > 0)
								{
									atmp3[ati8++] = '0' + av2 % 10;
									av2 /= 10;
								} 
								for (int x = ati8 - 1; x >= 0; x--)
								{
									astr4[asi8++] = atmp3[x];
								}
							}
							astr4[asi8] = '\0';

							const char* idlabel = "ID:";

							for (int x = 0; idlabel[x] != '\0'; x++)
							{
								pendingstr[pli++] = idlabel[x];
							}
							for (int x = 0; astr4[x] != '\0'; x++)
							{
								pendingstr[pli++] = astr4[x];
							}
							pendingstr[pli++] = ' ';

							// add date
							const char* dt3 = allapps3[a]->getdate();
							for (int x = 0; dt3[x] != '\0'; x++)
							{
								pendingstr[pli++] = dt3[x];
							}
							pendingstr[pli++] = ' ';

							// add slot
							const char* sl2 = allapps3[a]->getslot();
							for (int x = 0; sl2[x] != '\0'; x++)
							{
								pendingstr[pli++] = sl2[x];
							}
							pendingstr[pli++] = '\n';
						}
					}
					pendingstr[pli] = '\0';

					sf::Text pendinglist(font);
					pendinglist.setString(pendingstr);
					pendinglist.setCharacterSize(20);
					pendinglist.setFillColor(sf::Color(255, 140, 0));
					pendinglist.setPosition({ 50.f, 30.f });
					window.draw(pendinglist);

					window.draw(canceltext12);
					window.draw(cancelbutton12);
					window.draw(cancelbuttontext12);
					cancelbox12.drawscreen(window);
					window.draw(resulttext12);
				}
				//view my appointments
				else if (State == 13)
				{


					window.draw(background_Sprite2);

					char arr13[5000] = { 0 };
					int position13 = 0;
					Appointment** patappointrec = appointments.getall();
					int arr13index = appointments.getsize();

					Doctor** doctors13 = doctors.getall();
					int doctors13index = doctors.getsize();

					for (int m = 0; m < arr13index;m++)
					{
						if (patappointrec[m] != nullptr && patappointrec[m]->getpatid() == Patientcurrent->getId())
						{
							int appointid13 = patappointrec[m]->getid();


							int docid13 = patappointrec[m]->getdocid();
							const char* docname13 = "Unknown";
							const char* dospecialization13 = "N/A";

							for (int x = 0; x < doctors13index;x++)
							{
								if (doctors13[x] != nullptr && doctors13[x]->getId() == docid13)
								{
									docname13 = doctors13[x]->getName();
									dospecialization13 = doctors13[x]->getspecialization();
									break;
								}

							}



							const char* date13;
							date13 = patappointrec[m]->getdate();


							const char* slot13;
							slot13 = patappointrec[m]->getslot();

							const char* status13;
							status13 = patappointrec[m]->getstatus();

							int newid13 = patappointrec[m]->getid();
							char temparr13[20] = { 0 };
							int temppos13 = 0;


							if (newid13 == 0)
							{
								temparr13[temppos13++] = '0';
							}
							else
							{
								char temparr132[20];
								int temppos132 = 0;
								while (newid13 > 0)
								{
									temparr132[temppos132++] = newid13 % 10 + '0';
									newid13 = newid13 / 10;
								}
								while (temppos132 > 0)
								{
									temparr13[temppos13++] = temparr132[--temppos132];
								}

							}
							temparr13[temppos13] = '\0';

							const char* initial131 = "ID: ";
							const char* initial132 = "Doctor Name: ";
							const char* initial133 = "Specialization: ";
							const char* initial134 = "Date: ";
							const char* initial135 = "Time Slot: ";
							const char* initial136 = "Status: ";


							for (int n = 0; initial131[n] != '\0';n++)
							{
								arr13[position13++] = initial131[n];
							}


							for (int n = 0; temparr13[n] != '\0';n++)
							{
								arr13[position13++] = temparr13[n];
							}
							arr13[position13++] = '\n';

							for (int n = 0; initial132[n] != '\0';n++)
							{
								arr13[position13++] = initial132[n];
							}


							for (int n = 0; docname13[n] != '\0';n++)
							{
								arr13[position13++] = docname13[n];
							}
							arr13[position13++] = '\n';

							for (int n = 0; initial133[n] != '\0';n++)
							{
								arr13[position13++] = initial133[n];
							}


							for (int n = 0; dospecialization13[n] != '\0';n++)
							{
								arr13[position13++] = dospecialization13[n];
							}
							arr13[position13++] = '\n';

							for (int n = 0; initial134[n] != '\0';n++)
							{
								arr13[position13++] = initial134[n];
							}


							for (int n = 0; date13[n] != '\0';n++)
							{
								arr13[position13++] = date13[n];
							}
							arr13[position13++] = '\n';

							for (int n = 0; initial135[n] != '\0';n++)
							{
								arr13[position13++] = initial135[n];
							}


							for (int n = 0; slot13[n] != '\0';n++)
							{
								arr13[position13++] = slot13[n];
							}
							arr13[position13++] = '\n';

							for (int n = 0; initial136[n] != '\0';n++)
							{
								arr13[position13++] = initial136[n];
							}


							for (int n = 0; status13[n] != '\0';n++)
							{
								arr13[position13++] = status13[n];
							}
							arr13[position13++] = '\n';


						}
					}
					arr13[position13] = '\0';


					sf::Text patbutton13(font);
					if (arr13[0] == '\0')
					{
						patbutton13.setString("No appointments found for this patient");
					}
					else
					{
						patbutton13.setString(arr13);
					}
					patbutton13.setCharacterSize(32);
					patbutton13.setFillColor(sf::Color(255, 140, 0));
					patbutton13.setStyle(sf::Text::Bold);
					patbutton13.setPosition({ 70.f,80.f - scrollOffset });
					window.draw(patbutton13);
				}
				//view my medical records
				else if (State == 14)
				{
					window.draw(background_Sprite2);

					char arr14[5000];
					int position14 = 0;
					Prescription** patmedicalrec = prescriptions.getall();
					int arr14index = prescriptions.getsize();

					Doctor** doctors14 = doctors.getall();
					int doctors14index = doctors.getsize();

					for (int m = 0; m < arr14index;m++)
					{
						if (patmedicalrec[m] != nullptr && patmedicalrec[m]->getpatientid() == Patientcurrent->getId())
						{
							const char* date14;
							date14 = patmedicalrec[m]->getdate();

							int  doc14;
							doc14 = patmedicalrec[m]->getdoctorid();

							int docid14 = patmedicalrec[m]->getdoctorid();
							const char* docname14 = "Unknown Doctor";

							for (int x = 0; x < doctors14index;x++)
							{
								if (doctors14[x] != nullptr && doctors14[x]->getId() == docid14)
								{
									docname14 = doctors14[x]->getName();
									break;
								}

							}




							const char* medicine14;
							medicine14 = patmedicalrec[m]->getmedicines();

							const char* notes14;
							notes14 = patmedicalrec[m]->getnotes();


							const char* initial141 = "Date: ";
							const char* initial142 = "Doctor Name: ";
							const char* initial143 = "Medicines: ";
							const char* initial144 = "Notes: ";



							for (int n = 0; initial141[n] != '\0';n++)
							{
								arr14[position14++] = initial141[n];
							}


							for (int n = 0; date14[n] != '\0';n++)
							{
								arr14[position14++] = date14[n];
							}
							arr14[position14++] = '\n';

							for (int n = 0; initial142[n] != '\0';n++)
							{
								arr14[position14++] = initial142[n];
							}


							for (int n = 0; docname14[n] != '\0';n++)
							{
								arr14[position14++] = docname14[n];
							}
							arr14[position14++] = '\n';

							for (int n = 0; initial143[n] != '\0';n++)
							{
								arr14[position14++] = initial143[n];
							}


							for (int n = 0; medicine14[n] != '\0';n++)
							{
								arr14[position14++] = medicine14[n];
							}
							arr14[position14++] = '\n';

							for (int n = 0; initial144[n] != '\0';n++)
							{
								arr14[position14++] = initial144[n];
							}


							for (int n = 0; notes14[n] != '\0';n++)
							{
								arr14[position14++] = notes14[n];
							}
							arr14[position14++] = '\n';

						}
					}
					arr14[position14] = '\0';

					sf::Text patbutton14(font);
					if (arr14[0] == '\0')
					{
						patbutton14.setString("No medical records found for this patient");
					}
					else
					{
						patbutton14.setString(arr14);
					}
					patbutton14.setCharacterSize(32);
					patbutton14.setFillColor(sf::Color(255, 140, 0));
					patbutton14.setStyle(sf::Text::Bold);
					patbutton14.setPosition({ 70.f,80.f - scrollOffset });
					window.draw(patbutton14);
				}
				//view my bills
				else if (State == 15)
				{
					window.draw(background_Sprite2);

					char arr15[5000] = { 0 };
					int position15 = 0;
					Bill** patbillrec = bills.getall();
					int arr15index = bills.getsize();
					float billleft = 0;


					for (int m = 0; m < arr15index;m++)
					{
						if (patbillrec[m] != nullptr && patbillrec[m]->getpatid() == Patientcurrent->getId())
						{
							int billid15 = patbillrec[m]->getid();


							int newid15 = patbillrec[m]->getid();
							char temparr15[20] = { 0 };
							int temppos15 = 0;


							if (newid15 == 0)
							{
								temparr15[temppos15++] = '0';
							}
							else
							{
								char temparr152[20];
								int temppos152 = 0;
								while (newid15 > 0)
								{
									temparr152[temppos152++] = newid15 % 10 + '0';
									newid15 = newid15 / 10;
								}
								while (temppos152 > 0)
								{
									temparr15[temppos15++] = temparr152[--temppos152];
								}

							}
							temparr15[temppos15] = '\0';


							int appid15 = patbillrec[m]->getappid();

							int appnewid15 = patbillrec[m]->getappid();
							char apptemparr15[20] = { 0 };
							int apptemppos15 = 0;


							if (appnewid15 == 0)
							{
								apptemparr15[apptemppos15++] = '0';
							}
							else
							{
								char apptemparr152[20];
								int apptemppos152 = 0;
								while (appnewid15 > 0)
								{
									apptemparr152[apptemppos152++] = appnewid15 % 10 + '0';
									appnewid15 = appnewid15 / 10;
								}
								while (apptemppos152 > 0)
								{
									apptemparr15[apptemppos15++] = apptemparr152[--apptemppos152];
								}

							}
							apptemparr15[apptemppos15] = '\0';



							const char* date15;
							date15 = patbillrec[m]->getdate();


							const char* status15;
							status15 = patbillrec[m]->getstatus();


							if (Appointment::Comparechars(status15, "unpaid"))
							{
								billleft = billleft + patbillrec[m]->getamount();
							}

							const char* initial151 = "BILL ID: ";
							const char* initial152 = "APPOINTMENT ID: ";
							const char* initial153 = "AMOUNT(PKR): ";
							const char* initial154 = "STATUS: ";
							const char* initial155 = "DATE: ";


							for (int n = 0; initial151[n] != '\0';n++)
							{
								arr15[position15++] = initial151[n];
							}


							for (int n = 0; temparr15[n] != '\0';n++)
							{
								arr15[position15++] = temparr15[n];
							}
							arr15[position15++] = '\n';


							for (int n = 0; initial152[n] != '\0';n++)
							{
								arr15[position15++] = initial152[n];
							}


							for (int n = 0; apptemparr15[n] != '\0';n++)
							{
								arr15[position15++] = apptemparr15[n];
							}
							arr15[position15++] = '\n';

							for (int n = 0; initial153[n] != '\0';n++)
							{
								arr15[position15++] = initial153[n];
							}


							float amount15 = patbillrec[m]->getamount();
							int newamount15 = (int)amount15;
							char amountarr15[20] = { 0 };
							int amountposition15 = 0;

							if (newamount15 == 0)
							{
								amountarr15[amountposition15++] = '0';
							}
							else
							{
								char tempamountarr15[20];
								int tempamountposition15 = 0;
								while (newamount15 > 0)
								{
									tempamountarr15[tempamountposition15++] = newamount15 % 10 + '0';
									newamount15 = newamount15 / 10;
								}
								while (tempamountposition15 > 0)
								{
									amountarr15[amountposition15++] = tempamountarr15[--tempamountposition15];
								}
							}
							amountarr15[amountposition15] = '\0';

							for (int n = 0; amountarr15[n] != '\0'; n++)
							{
								arr15[position15++] = amountarr15[n];
							}
							arr15[position15++] = '\n';


							for (int n = 0; initial154[n] != '\0';n++)
							{
								arr15[position15++] = initial154[n];
							}

							for (int n = 0; status15[n] != '\0';n++)
							{
								arr15[position15++] = status15[n];
							}
							arr15[position15++] = '\n';


							for (int n = 0; initial155[n] != '\0';n++)
							{
								arr15[position15++] = initial155[n];
							}

							for (int n = 0; date15[n] != '\0';n++)
							{
								arr15[position15++] = date15[n];
							}
							arr15[position15++] = '\n';



						}
					}
					arr15[position15] = '\0';

					const char* totallabel15 = "TOTAL UNPAID AMOUNT: PKR ";
					for (int n = 0; totallabel15[n] != '\0'; n++)
					{

						arr15[position15++] = totallabel15[n];
					}

					int newbillleft15 = (int)billleft;
					char billtmp[20];
					int billtmppos15 = 0;
					char billarr[20];
					int billarrpos15 = 0;

					if (newbillleft15 == 0)
					{
						billarr[billarrpos15++] = '0';
					}
					else
					{
						while (newbillleft15 > 0)
						{
							billtmp[billtmppos15++] = newbillleft15 % 10 + '0';
							newbillleft15 = newbillleft15 / 10;
						}
						while (billtmppos15 > 0)
						{
							billarr[billarrpos15++] = billtmp[--billtmppos15];
						}
					}

					billarr[billarrpos15] = '\0';
					for (int n = 0; billarr[n] != '\0'; n++)
					{
						arr15[position15++] = billarr[n];
					}
					arr15[position15++] = '\n';

					sf::Text patbutton15(font);
					if (arr15[0] == '\0')
					{
						patbutton15.setString("No bills found for this patient");
					}
					else
					{
						patbutton15.setString(arr15);
					}
					patbutton15.setCharacterSize(32);
					patbutton15.setFillColor(sf::Color(255, 140, 0));
					patbutton15.setStyle(sf::Text::Bold);
					patbutton15.setPosition({ 70.f,80.f - scrollOffset });
					window.draw(patbutton15);
				}
				//PAY BILL
				else if (State == 16)
				{
					window.draw(background_Sprite2);

					// showing unpaid bills
					char unpaidstr[500];
					int uli = 0;
					Bill** allbills5 = bills.getall();
					int bcount5 = bills.getsize();
					for (int b = 0; b < bcount5; b++)
					{
						if (allbills5[b]->getpatid() == Patientcurrent->getId() &&
							Appointment::Comparechars(allbills5[b]->getstatus(), "unpaid"))
						{
							int bv2 = allbills5[b]->getid();
							char bstr5[10];
							int bsi7 = 0;
							char btmp5[10];
							int bti7 = 0;

							if (bv2 == 0)
							{
								bstr5[bsi7++] = '0'; 
							}
							else 
							{
								while (bv2 > 0)
								{
									btmp5[bti7++] = '0' + bv2 % 10;
									bv2 =bv2/ 10;
								}
								for (int x = bti7 - 1; x >= 0; x--)
								{
									bstr5[bsi7++] = btmp5[x];
								}
							}
							bstr5[bsi7] = '\0';

							const char* bl2 = "BillID:";

							for (int x = 0; bl2[x] != '\0'; x++)
							{
								unpaidstr[uli++] = bl2[x];
							}
							for (int x = 0; bstr5[x] != '\0'; x++)
							{
								unpaidstr[uli++] = bstr5[x];
							}
							unpaidstr[uli++] = ' ';

							float amtv3 = allbills5[b]->getamount();
							int amtint3 = (int)amtv3;
							char amttmp3[10];
							int amtti3 = 0;
							char amtstr3[20];
							int amtsi3 = 0;

							if (amtint3 == 0)
							{
								amtstr3[amtsi3++] = '0'; 
							}
							else 
							{ 
								while (amtint3 > 0)
								{
									amttmp3[amtti3++] = '0' + amtint3 % 10;
									amtint3 =amtint3/ 10;
								}
								for (int x = amtti3 - 1; x >= 0; x--)
								{
									amtstr3[amtsi3++] = amttmp3[x];
								}
							}
							amtstr3[amtsi3] = '\0';
							const char* pkl = " PKR:";
							for (int x = 0; pkl[x] != '\0'; x++)
							{
								unpaidstr[uli++] = pkl[x];
							}
							for (int x = 0; amtstr3[x] != '\0'; x++)
							{
								unpaidstr[uli++] = amtstr3[x];
							}
							unpaidstr[uli++] = '\n';
						}
					}
					unpaidstr[uli] = '\0';

					sf::Text unpaidlist(font);
					unpaidlist.setString(unpaidstr[0] != '\0' ? unpaidstr : "No unpaid bills.");
					unpaidlist.setCharacterSize(20);
					unpaidlist.setFillColor(sf::Color(255, 140, 0));
					unpaidlist.setPosition({ 50.f, 30.f });
					window.draw(unpaidlist);

					window.draw(paybilltext16);
					window.draw(paybillbutton16);
					window.draw(paybillbuttontext16);
					paybillbox16.drawscreen(window);
					window.draw(resulttext16);
				}//TOP UP BALANCE
				else if (State == 17)
				{
					window.draw(background_Sprite2);
					window.draw(topuptext17);
					window.draw(topupbutton17);
					window.draw(topupbuttontext17);
					topupbox17.drawscreen(window);
					window.draw(resulttext17);
				}
				//View Todays's Appointments
				else if (State == 21)
				{
					window.draw(background_Sprite2);

					time_t time21 = time(0);
					tm* localtime21 = localtime(&time21);
					char timearr21[11];
					strftime(timearr21, 11, "%d-%m-%Y", localtime21);

					char arr21[5000] = { 0 };
					int position21 = 0;
					Appointment** docappointrec = appointments.getall();
					int arr21index = appointments.getsize();


					for (int m = 0; m < arr21index;m++)
					{
						if (Appointment::Comparechars(docappointrec[m]->getdate(), timearr21) && docappointrec[m] != nullptr && docappointrec[m]->getdocid() == Doctorcurrent->getId())
						{
							int appointid21 = docappointrec[m]->getid();


							int newid21 = docappointrec[m]->getid();
							char temparr21[20] = { 0 };
							int temppos21 = 0;


							if (newid21 == 0)
							{
								temparr21[temppos21++] = '0';
							}
							else
							{
								char temparr212[20];
								int temppos212 = 0;
								while (newid21 > 0)
								{
									temparr212[temppos212++] = newid21 % 10 + '0';
									newid21 = newid21 / 10;
								}
								while (temppos212 > 0)
								{
									temparr21[temppos21++] = temparr212[--temppos212];
								}

							}
							temparr21[temppos21] = '\0';



							int patid21 = docappointrec[m]->getpatid();
							const char* patname21 = "";
							Patient** allPats21 = patients.getall();
							int totalPats21 = patients.getsize();

							for (int p = 0; p < totalPats21; p++) {
								if (allPats21[p] != nullptr && allPats21[p]->getId() == patid21) {
									patname21 = allPats21[p]->getName();
									break;
								}
							}


							const char* slot21;
							slot21 = docappointrec[m]->getslot();

							const char* status21;
							status21 = docappointrec[m]->getstatus();



							const char* initial211 = "Appointment ID: ";
							const char* initial212 = "Patient Name: ";
							const char* initial213 = "TimeSlot: ";
							const char* initial214 = "Status: ";



							for (int n = 0; initial211[n] != '\0';n++)
							{
								arr21[position21++] = initial211[n];
							}


							for (int n = 0; temparr21[n] != '\0';n++)
							{
								arr21[position21++] = temparr21[n];
							}
							arr21[position21++] = '\n';

							for (int n = 0; initial212[n] != '\0';n++)
							{
								arr21[position21++] = initial212[n];
							}


							for (int n = 0; patname21[n] != '\0';n++)
							{
								arr21[position21++] = patname21[n];
							}
							arr21[position21++] = '\n';

							for (int n = 0; initial213[n] != '\0';n++)
							{
								arr21[position21++] = initial213[n];
							}


							for (int n = 0; slot21[n] != '\0';n++)
							{
								arr21[position21++] = slot21[n];
							}
							arr21[position21++] = '\n';

							for (int n = 0; initial214[n] != '\0';n++)
							{
								arr21[position21++] = initial214[n];
							}


							for (int n = 0; status21[n] != '\0';n++)
							{
								arr21[position21++] = status21[n];
							}
							arr21[position21++] = '\n';




						}
					}
					arr21[position21] = '\0';


					sf::Text docbutton21(font);
					if (arr21[0] == '\0')
					{
						docbutton21.setString("No appointments scheduled for today");
					}
					else
					{
						docbutton21.setString(arr21);
					}
					docbutton21.setCharacterSize(32);
					docbutton21.setFillColor(sf::Color(255, 140, 0));
					docbutton21.setStyle(sf::Text::Bold);
					docbutton21.setPosition({ 70.f,80.f - scrollOffset });
					window.draw(docbutton21);
				}
				//Mark Appointment Complete
				else if (State == 22)
				{
					window.draw(background_Sprite2);
					time_t tnow5 = time(0);
					tm* tloc5 = localtime(&tnow5);
					char todaystr5[11];
					strftime(todaystr5, 11, "%d-%m-%Y", tloc5);

					char pendstr2[500];
					int pli3 = 0;
					Appointment** allapps10 = appointments.getall();
					int acount10 = appointments.getsize();
					for (int a = 0; a < acount10; a++)
					{
						if (allapps10[a]->getdocid() == Doctorcurrent->getId() &&
							Appointment::Comparechars(allapps10[a]->getstatus(), "pending") &&
							Appointment::Comparechars(allapps10[a]->getdate(), todaystr5))
						{
							int av5 = allapps10[a]->getid();
							char astr7[10];
							int asi11 = 0;
							char atmp6[10];
							int ati11 = 0;

							if (av5 == 0)
							{
								astr7[asi11++] = '0';
							}
							else 
							{
								while (av5 > 0)
								{
									atmp6[ati11++] = '0' + av5 % 10;
									av5 =av5/ 10; 
								}
								for (int x = ati11 - 1;x >= 0;x--)
								{
									astr7[asi11++] = atmp6[x];
								}
							}
							astr7[asi11] = '\0';

							const char* idl3 = "ID:";
							for (int x = 0;idl3[x] != '\0';x++)
							{
								pendstr2[pli3++] = idl3[x];
							}
							for (int x = 0;astr7[x] != '\0';x++)
							{
								pendstr2[pli3++] = astr7[x];
							}
							pendstr2[pli3++] = ' ';
							const char* sl7 = allapps10[a]->getslot();
							for (int x = 0;sl7[x] != '\0';x++)
							{
								pendstr2[pli3++] = sl7[x];
							}
							pendstr2[pli3++] = '\n';
						}
					}
					pendstr2[pli3] = '\0';

					sf::Text pendlist2(font);
					pendlist2.setString(pli3 > 0 ? pendstr2 : "No pending appointments today.");
					pendlist2.setCharacterSize(20);
					pendlist2.setFillColor(sf::Color(255, 140, 0));
					pendlist2.setPosition({ 50.f, 40.f });
					window.draw(pendlist2);

					window.draw(markcompletetext22);
					window.draw(markcompletebutton22);
					window.draw(markcompletebuttontext22);
					markcompletebox22.drawscreen(window);
					window.draw(docresulttext22);
				}
				//Mark Appointment No show
				else if (State == 23)
				{
					window.draw(background_Sprite2);

					// show today pending appointments
					time_t tnow6 = time(0);
					tm* tloc6 = localtime(&tnow6);
					char todaystr6[11];
					strftime(todaystr6, 11, "%d-%m-%Y", tloc6);

					char pendstr3[500];
					int pli4 = 0;
					Appointment** allapps11 = appointments.getall();
					int acount11 = appointments.getsize();
					for (int a = 0; a < acount11; a++)
					{
						if (allapps11[a]->getdocid() == Doctorcurrent->getId() &&
							Appointment::Comparechars(allapps11[a]->getstatus(), "pending") &&
							Appointment::Comparechars(allapps11[a]->getdate(), todaystr6))
						{
							int av6 = allapps11[a]->getid();
							char astr8[10];
							int asi12 = 0; 
							char atmp7[10];
							int ati12 = 0;

							if (av6 == 0)
							{
								astr8[asi12++] = '0'; 
							}
							else 
							{
								while (av6 > 0)
								{
									atmp7[ati12++] = '0' + av6 % 10;
									av6 =av6/ 10; 
								}
								for (int x = ati12 - 1;x >= 0;x--)
								{
									astr8[asi12++] = atmp7[x];
								}
							}
							astr8[asi12] = '\0';

							for (int x = 0;astr8[x] != '\0';x++)
							{
								pendstr3[pli4++] = astr8[x];
							}
							pendstr3[pli4++] = ' ';

							const char* sl8 = allapps11[a]->getslot();

							for (int x = 0;sl8[x] != '\0';x++)
							{
								pendstr3[pli4++] = sl8[x];
							}
							pendstr3[pli4++] = '\n';
						}
					}
					pendstr3[pli4] = '\0';

					sf::Text pendlist3(font);
					pendlist3.setString(pli4 > 0 ? pendstr3 : "No pending appointments today.");
					pendlist3.setCharacterSize(20);
					pendlist3.setFillColor(sf::Color(255, 140, 0));
					pendlist3.setPosition({ 50.f, 40.f });
					window.draw(pendlist3);

					window.draw(marknoshowtext23);
					window.draw(marknoshbutton23);
					window.draw(marknoshbuttontext23);
					marknoshowbox23.drawscreen(window);
					window.draw(docresulttext23);
				}
				//Write Prescription
				else if (State == 24)
				{
					window.draw(background_Sprite2);
					window.draw(prescapptext24);
					window.draw(prescmedtext24);
					window.draw(prescnotestext24);
					window.draw(prescbutton24);
					window.draw(prescbuttontext24);
					prescappbox24.drawscreen(window);
					prescmedbox24.drawscreen(window);
					prescnotesbox24.drawscreen(window);
					window.draw(docresulttext24);
				}
				//View Patient's Medical History
				else if (State == 25)
				{
					window.draw(background_Sprite2);
					window.draw(pathistorytext25);
					window.draw(historybutton25);
					window.draw(histbuttontext25);
					pathistorybox25.drawscreen(window);
					window.draw(historyresult25);
					window.draw(docresulttext25);
				}
				//ADD DOCTOR
				else if (State == 31)
				{
					window.draw(background_Sprite2);
					window.draw(docname31);
					window.draw(docspec31);
					window.draw(doccont31);
					window.draw(docpass31);
					window.draw(docfee31);
					window.draw(addDocbutton);
					window.draw(doctbutton31);
					docnamebox31.drawscreen(window);
					docspecbox31.drawscreen(window);
					doccontbox31.drawscreen(window);
					docpassbox31.drawscreen(window);
					docfeebox31.drawscreen(window);
					window.draw(adminresulttext371);
				}
				//REMOVE DOCTOR
				else if (State == 32)
				{
					window.draw(background_Sprite2);


					char showdocarray32[500];
					int dli32 = 0;
					Doctor** alldocsarr = doctors.getall();
					int newdcount32 = doctors.getsize();

					for (int d = 0; d < newdcount32; d++)
					{
						int dv3 = alldocsarr[d]->getId();

						char dtmp3[10];
						int dti2 = 0;
						char dstr3[10];
						int dsi3 = 0;

						if (dv3 == 0)
						{
							dstr3[dsi3++] = '0';
						}
						else
						{
							while (dv3 > 0)
							{
								dtmp3[dti2++] = '0' + dv3 % 10;
								dv3 = dv3 / 10;
							}
							for (int x = dti2 - 1;x >= 0;x--)
							{
								dstr3[dsi3++] = dtmp3[x];
							}
						}
						dstr3[dsi3] = '\0';

						const char* idl32 = "ID:";
						for (int x = 0;idl32[x] != '\0';x++)
						{
							showdocarray32[dli32++] = idl32[x];
						}
						for (int x = 0;dstr3[x] != '\0';x++)
						{
							showdocarray32[dli32++] = dstr3[x];
						}
						showdocarray32[dli32++] = ' ';

						const char* dn2 = alldocsarr[d]->getName();

						for (int x = 0;dn2[x] != '\0';x++)
						{
							showdocarray32[dli32++] = dn2[x];
						}
						showdocarray32[dli32++] = ' ';

						const char* ds3 = alldocsarr[d]->getspecialization();

						for (int x = 0;ds3[x] != '\0';x++)
						{
							showdocarray32[dli32++] = ds3[x];
						}
						showdocarray32[dli32++] = '\n';
					}
					showdocarray32[dli32] = '\0';

					sf::Text doclist2(font);
					if (dli32 > 0)
					{
						doclist2.setString(showdocarray32);
					}
					else
					{
						doclist2.setString("No doctors found.");
					}
					doclist2.setCharacterSize(20);
					doclist2.setFillColor(sf::Color::Black);
					doclist2.setPosition({ 50.f, 100.f });
					window.draw(doclist2);

					window.draw(removedoc32);
					window.draw(removedocbutton32);
					window.draw(removedocbuttontext32);
					removedocbox32.drawscreen(window);
					window.draw(adminresulttext372);
				}
				//VIEW ALL PATIENTS
				else if (State == 33)
				{
					window.draw(background_Sprite2);

					char arr33[10000];
					int position33 = 0;
					Patient** admpatientrec = patients.getall();
					int arr33index = patients.getsize();



					for (int m = 0; m < arr33index;m++)
					{


						int patientid33 = admpatientrec[m]->getId();


						int newid33 = admpatientrec[m]->getId();
						char temparr33[20] = { 0 };
						int temppos33 = 0;


						if (newid33 == 0)
						{
							temparr33[temppos33++] = '0';
						}
						else
						{
							char temparr332[20];
							int temppos332 = 0;
							while (newid33 > 0)
							{
								temparr332[temppos332++] = newid33 % 10 + '0';
								newid33 = newid33 / 10;
							}
							while (temppos332 > 0)
							{
								temparr33[temppos33++] = temparr332[--temppos332];
							}

						}
						temparr33[temppos33] = '\0';




						const char* name33;
						name33 = admpatientrec[m]->getName();


						int patientage33 = admpatientrec[m]->getage();


						int newage33 = admpatientrec[m]->getage();
						char agetemparr33[20] = { 0 };
						int agetemppos33 = 0;


						if (newage33 == 0)
						{
							agetemparr33[agetemppos33++] = '0';
						}
						else
						{
							char agetemparr332[20];
							int agetemppos332 = 0;
							while (newage33 > 0)
							{
								agetemparr332[agetemppos332++] = newage33 % 10 + '0';
								newage33 = newage33 / 10;
							}
							while (agetemppos332 > 0)
							{
								agetemparr33[agetemppos33++] = agetemparr332[--agetemppos332];
							}

						}
						agetemparr33[agetemppos33] = '\0';

						char gender33;
						gender33 = admpatientrec[m]->getgender();

						const char* contact33;
						contact33 = admpatientrec[m]->getcontact();

						int patientbalance33 = admpatientrec[m]->getbalance();


						int newbalance33 = admpatientrec[m]->getbalance();
						char balancetemparr33[20] = { 0 };
						int balancetemppos33 = 0;


						if (newbalance33 == 0)
						{
							balancetemparr33[balancetemppos33++] = '0';
						}
						else
						{
							char balancetemparr332[20];
							int balancetemppos332 = 0;
							while (newbalance33 > 0)
							{
								balancetemparr332[balancetemppos332++] = newbalance33 % 10 + '0';
								newbalance33 = newbalance33 / 10;
							}
							while (balancetemppos332 > 0)
							{
								balancetemparr33[balancetemppos33++] = balancetemparr332[--balancetemppos332];
							}

						}
						balancetemparr33[balancetemppos33] = '\0';



						int U_billscount33 = 0;
						Bill** admbills33 = bills.getall();
						int countBills33 = bills.getsize();

						for (int z = 0; z < countBills33; z++)
						{
							if (admbills33[z] != nullptr && admbills33[z]->getpatid() == patientid33)
							{
								const char* billpatstatus = admbills33[z]->getstatus();

								if (billpatstatus != nullptr && (billpatstatus[0] == 'U' || billpatstatus[0] == 'u'))
								{
									U_billscount33++;
								}

							}

						}

						char billtemparray33[10] = { 0 };
						int billcounttemp33 = U_billscount33;
						int countPos33 = 0;

						if (billcounttemp33 == 0)
						{
							billtemparray33[countPos33++] = '0';
						}
						else
						{
							char billtemparray332[10];
							int billcounttemp332 = 0;
							while (billcounttemp33 > 0)
							{
								billtemparray332[billcounttemp332++] = (billcounttemp33 % 10) + '0';
								billcounttemp33 = billcounttemp33 / 10;
							}
							while (billcounttemp332 > 0)
							{
								billtemparray33[countPos33++] = billtemparray332[--billcounttemp332];
							}
						}
						billtemparray33[countPos33] = '\0';


						const char* initial331 = "Patient ID: ";
						const char* initial332 = "Name: ";
						const char* initial333 = "Age: ";
						const char* initial334 = "Gender: ";
						const char* initial335 = "Contact: ";
						const char* initial336 = "Balance: ";
						const char* initial337 = "Count of Unpaid Bills: ";





						for (int n = 0; initial331[n] != '\0';n++)
						{
							arr33[position33++] = initial331[n];
						}


						for (int n = 0; temparr33[n] != '\0';n++)
						{
							arr33[position33++] = temparr33[n];
						}
						arr33[position33++] = '\n';

						for (int n = 0; initial332[n] != '\0';n++)
						{
							arr33[position33++] = initial332[n];
						}


						for (int n = 0; name33[n] != '\0';n++)
						{
							arr33[position33++] = name33[n];
						}
						arr33[position33++] = '\n';

						for (int n = 0; initial333[n] != '\0';n++)
						{
							arr33[position33++] = initial333[n];
						}


						for (int n = 0; agetemparr33[n] != '\0';n++)
						{
							arr33[position33++] = agetemparr33[n];
						}
						arr33[position33++] = '\n';

						for (int n = 0; initial334[n] != '\0';n++)
						{
							arr33[position33++] = initial334[n];
						}


						arr33[position33++] = gender33;
						arr33[position33++] = '\n';

						for (int n = 0; initial335[n] != '\0';n++)
						{
							arr33[position33++] = initial335[n];
						}


						for (int n = 0; contact33[n] != '\0';n++)
						{
							arr33[position33++] = contact33[n];
						}
						arr33[position33++] = '\n';


						for (int n = 0; initial336[n] != '\0';n++)
						{
							arr33[position33++] = initial336[n];
						}


						for (int n = 0; balancetemparr33[n] != '\0';n++)
						{
							arr33[position33++] = balancetemparr33[n];
						}
						arr33[position33++] = '\n';

						for (int n = 0; initial337[n] != '\0';n++)
						{
							arr33[position33++] = initial337[n];
						}


						for (int n = 0; billtemparray33[n] != '\0';n++)
						{
							arr33[position33++] = billtemparray33[n];
						}
						arr33[position33++] = '\n';



					}
					arr33[position33] = '\0';

					sf::Text admbutton33(font);
					if (arr33[0] == '\0')
					{
						admbutton33.setString("No patients found to display");
					}
					else
					{
						admbutton33.setString(arr33);
					}
					admbutton33.setCharacterSize(32);
					admbutton33.setFillColor(sf::Color(255, 140, 0));
					admbutton33.setStyle(sf::Text::Bold);
					admbutton33.setPosition({ 70.f,80.f - scrollOffset });
					window.draw(admbutton33);
				}
				//VIEW ALL DOCTORS
				else if (State == 34)
				{
					window.draw(background_Sprite2);

					char arr34[10000];
					int position34 = 0;
					Doctor** admdoctorrec = doctors.getall();
					int arr34index = doctors.getsize();



					for (int m = 0; m < arr34index;m++)
					{


						int doctorid34 = admdoctorrec[m]->getId();


						int newid34 = admdoctorrec[m]->getId();
						char temparr34[20] = { 0 };
						int temppos34 = 0;


						if (newid34 == 0)
						{
							temparr34[temppos34++] = '0';
						}
						else
						{
							char temparr342[20];
							int temppos342 = 0;
							while (newid34 > 0)
							{
								temparr342[temppos342++] = newid34 % 10 + '0';
								newid34 = newid34 / 10;
							}
							while (temppos342 > 0)
							{
								temparr34[temppos34++] = temparr342[--temppos342];
							}

						}
						temparr34[temppos34] = '\0';




						const char* name34;
						name34 = admdoctorrec[m]->getName();

						const char* specialization34;
						specialization34 = admdoctorrec[m]->getspecialization();


						const char* contact34;
						contact34 = admdoctorrec[m]->getcontact();


						int patientfee34 = admdoctorrec[m]->getfee();


						int newfee34 = admdoctorrec[m]->getfee();
						char feetemparr34[20] = { 0 };
						int feetemppos34 = 0;


						if (newfee34 == 0)
						{
							feetemparr34[feetemppos34++] = '0';
						}
						else
						{
							char feetemparr342[20];
							int feetemppos342 = 0;
							while (newfee34 > 0)
							{
								feetemparr342[feetemppos342++] = newfee34 % 10 + '0';
								newfee34 = newfee34 / 10;
							}
							while (feetemppos342 > 0)
							{
								feetemparr34[feetemppos34++] = feetemparr342[--feetemppos342];
							}

						}
						feetemparr34[feetemppos34] = '\0';






						const char* initial341 = "Doctor ID: ";
						const char* initial342 = "Name: ";
						const char* initial343 = "Specialization: ";
						const char* initial344 = "Contact: ";
						const char* initial345 = "Fee: ";





						for (int n = 0; initial341[n] != '\0';n++)
						{
							arr34[position34++] = initial341[n];
						}


						for (int n = 0; temparr34[n] != '\0';n++)
						{
							arr34[position34++] = temparr34[n];
						}
						arr34[position34++] = '\n';

						for (int n = 0; initial342[n] != '\0';n++)
						{
							arr34[position34++] = initial342[n];
						}


						for (int n = 0; name34[n] != '\0';n++)
						{
							arr34[position34++] = name34[n];
						}
						arr34[position34++] = '\n';

						for (int n = 0; initial343[n] != '\0';n++)
						{
							arr34[position34++] = initial343[n];
						}


						for (int n = 0; specialization34[n] != '\0';n++)
						{
							arr34[position34++] = specialization34[n];
						}
						arr34[position34++] = '\n';

						for (int n = 0; initial344[n] != '\0';n++)
						{
							arr34[position34++] = initial344[n];
						}
						for (int n = 0; contact34[n] != '\0';n++)
						{
							arr34[position34++] = contact34[n];
						}
						arr34[position34++] = '\n';


						for (int n = 0; initial345[n] != '\0';n++)
						{
							arr34[position34++] = initial345[n];
						}

						for (int n = 0; feetemparr34[n] != '\0';n++)
						{
							arr34[position34++] = feetemparr34[n];
						}
						arr34[position34++] = '\n';






					}
					arr34[position34] = '\0';

					sf::Text admbutton34(font);
					if (arr34[0] == '\0')
					{
						admbutton34.setString("No doctors found to display");
					}
					else
					{
						admbutton34.setString(arr34);
					}
					admbutton34.setCharacterSize(32);
					admbutton34.setFillColor(sf::Color(255, 140, 0));
					admbutton34.setStyle(sf::Text::Bold);
					admbutton34.setPosition({ 70.f,80.f - scrollOffset });
					window.draw(admbutton34);
				}
				//VIEW ALL APPOINTMENTS
				else if (State == 35)
				{
					window.draw(background_Sprite2);
					char arr35[10000];
					int position35 = 0;
					Appointment** admappointrec = appointments.getall();
					int arr35index = appointments.getsize();



					for (int m = 0; m < arr35index;m++)
					{


						int appointid35 = admappointrec[m]->getid();


						int newid35 = admappointrec[m]->getid();
						char temparr35[20] = { 0 };
						int temppos35 = 0;


						if (newid35 == 0)
						{
							temparr35[temppos35++] = '0';
						}
						else
						{
							char temparr352[20];
							int temppos352 = 0;
							while (newid35 > 0)
							{
								temparr352[temppos352++] = newid35 % 10 + '0';
								newid35 = newid35 / 10;
							}
							while (temppos352 > 0)
							{
								temparr35[temppos35++] = temparr352[--temppos352];
							}

						}
						temparr35[temppos35] = '\0';




						int patid35;
						patid35 = admappointrec[m]->getpatid();


						const char* patientName35 = "";

						Patient** patientsearch35 = patients.getall();
						int patientcount35 = patients.getsize();

						for (int p = 0; p < patientcount35; p++)
						{
							if (patientsearch35[p] != nullptr && patientsearch35[p]->getId() == patid35)
							{
								patientName35 = patientsearch35[p]->getName();
								break;
							}
						}


						int docid35;
						docid35 = admappointrec[m]->getdocid();


						const char* doctorName35 = "";

						Doctor** doctorsearch35 = doctors.getall();
						int doctorcount35 = doctors.getsize();

						for (int p = 0; p < doctorcount35; p++)
						{
							if (doctorsearch35[p] != nullptr && doctorsearch35[p]->getId() == docid35)
							{
								doctorName35 = doctorsearch35[p]->getName();
								break;
							}
						}

						const char* date35;
						date35 = admappointrec[m]->getdate();

						const char* slot35;
						slot35 = admappointrec[m]->getslot();

						const char* status35;
						status35 = admappointrec[m]->getstatus();













						const char* initial351 = "Appointment ID: ";
						const char* initial352 = "Patient Name: ";
						const char* initial353 = "Doctor Name: ";
						const char* initial354 = "Date: ";
						const char* initial355 = "Time Slot: ";
						const char* initial356 = "Status: ";





						for (int n = 0; initial351[n] != '\0';n++)
						{
							arr35[position35++] = initial351[n];
						}


						for (int n = 0; temparr35[n] != '\0';n++)
						{
							arr35[position35++] = temparr35[n];
						}
						arr35[position35++] = '\n';

						for (int n = 0; initial352[n] != '\0';n++)
						{
							arr35[position35++] = initial352[n];
						}


						for (int n = 0; patientName35[n] != '\0';n++)
						{
							arr35[position35++] = patientName35[n];
						}
						arr35[position35++] = '\n';

						for (int n = 0; initial353[n] != '\0';n++)
						{
							arr35[position35++] = initial353[n];
						}


						for (int n = 0; doctorName35[n] != '\0';n++)
						{
							arr35[position35++] = doctorName35[n];
						}
						arr35[position35++] = '\n';

						for (int n = 0; initial354[n] != '\0';n++)
						{
							arr35[position35++] = initial354[n];
						}

						for (int n = 0; date35[n] != '\0';n++)
						{
							arr35[position35++] = date35[n];
						}
						arr35[position35++] = '\n';


						for (int n = 0; initial355[n] != '\0';n++)
						{
							arr35[position35++] = initial355[n];
						}


						for (int n = 0; slot35[n] != '\0';n++)
						{
							arr35[position35++] = slot35[n];
						}
						arr35[position35++] = '\n';


						for (int n = 0; initial356[n] != '\0';n++)
						{
							arr35[position35++] = initial356[n];
						}


						for (int n = 0; status35[n] != '\0';n++)
						{
							arr35[position35++] = status35[n];
						}
						arr35[position35++] = '\n';





					}
					arr35[position35] = '\0';

					sf::Text admbutton35(font);
					if (arr35[0] == '\0')
					{
						admbutton35.setString("No appointments found to display");
					}
					else
					{
						admbutton35.setString(arr35);
					}
					admbutton35.setCharacterSize(32);
					admbutton35.setFillColor(sf::Color(255, 140, 0));
					admbutton35.setStyle(sf::Text::Bold);
					admbutton35.setPosition({ 70.f,80.f - scrollOffset });
					window.draw(admbutton35);
				}
				//VIEW UNPAID BILLS
				else if (State == 36)
				{
					window.draw(background_Sprite2);

					time_t now36 = time(0);
					tm* timelocal36 = localtime(&now36);

					char arr36[1000] = { 0 };
					int position36 = 0;
					Bill** admbillrec = bills.getall();

					for (int m = 0;m < bills.getsize();m++)
					{

						if (!Appointment::Comparechars(admbillrec[m]->getstatus(), "unpaid"))
						{
							continue;
						}

						int billid36 = admbillrec[m]->getid();


						int newid36 = admbillrec[m]->getid();
						char temparr36[20] = { 0 };
						int temppos36 = 0;


						if (newid36 == 0)
						{
							temparr36[temppos36++] = '0';
						}
						else
						{
							char temparr362[20];
							int temppos362 = 0;
							while (newid36 > 0)
							{
								temparr362[temppos362++] = newid36 % 10 + '0';
								newid36 = newid36 / 10;
							}
							while (temppos362 > 0)
							{
								temparr36[temppos36++] = temparr362[--temppos362];
							}

						}
						temparr36[temppos36] = '\0';




						int patid36;
						patid36 = admbillrec[m]->getpatid();


						const char* patientName36 = "";

						Patient** patientsearch36 = patients.getall();
						int patientcount36 = patients.getsize();

						for (int p = 0; p < patientcount36; p++)
						{
							if (patientsearch36[p] != nullptr && patientsearch36[p]->getId() == patid36)
							{
								patientName36 = patientsearch36[p]->getName();
								break;
							}
						}


						float amount36 = admbillrec[m]->getamount();
						int newamount36 = (int)amount36;
						char amountarr36[20] = { 0 };
						int amountposition36 = 0;

						if (newamount36 == 0)
						{
							amountarr36[amountposition36++] = '0';
						}
						else
						{
							char tempamountarr36[20];
							int tempamountposition36 = 0;
							while (newamount36 > 0)
							{
								tempamountarr36[tempamountposition36++] = newamount36 % 10 + '0';
								newamount36 = newamount36 / 10;
							}
							while (tempamountposition36 > 0)
							{
								amountarr36[amountposition36++] = tempamountarr36[--tempamountposition36];
							}
						}
						amountarr36[amountposition36] = '\0';




						const char* date36;
						date36 = admbillrec[m]->getdate();


						const char* initial361 = "Bill ID: ";
						const char* initial362 = "Patient Name: ";
						const char* initial363 = "Amount(PKR): ";
						const char* initial364 = "Date: ";





						for (int n = 0; initial361[n] != '\0';n++)
						{
							arr36[position36++] = initial361[n];
						}


						for (int n = 0; temparr36[n] != '\0';n++)
						{
							arr36[position36++] = temparr36[n];
						}
						arr36[position36++] = '\n';

						for (int n = 0; initial362[n] != '\0';n++)
						{
							arr36[position36++] = initial362[n];
						}


						for (int n = 0; patientName36[n] != '\0';n++)
						{
							arr36[position36++] = patientName36[n];
						}
						arr36[position36++] = '\n';

						for (int n = 0; initial363[n] != '\0';n++)
						{
							arr36[position36++] = initial363[n];
						}


						for (int n = 0; amountarr36[n] != '\0';n++)
						{
							arr36[position36++] = amountarr36[n];
						}
						arr36[position36++] = '\n';

						for (int n = 0; initial364[n] != '\0';n++)
						{
							arr36[position36++] = initial364[n];
						}

						for (int n = 0; date36[n] != '\0';n++)
						{
							arr36[position36++] = date36[n];
						}
						arr36[position36++] = '\n';




						int daysbefore36 = (date36[0] - '0') * 10 + (date36[1] - '0');

						int monthsbefore36 = (date36[3] - '0') * 10 + (date36[4] - '0');

						int yearsbefore36 = (date36[6] - '0') * 1000 + (date36[7] - '0') * 100 + (date36[8] - '0') * 10 + (date36[9] - '0');

						tm beforetoday36 = {};
						beforetoday36.tm_mday = daysbefore36;

						beforetoday36.tm_mon = monthsbefore36 - 1;
						beforetoday36.tm_year = yearsbefore36 - 1900;
						beforetoday36.tm_isdst = -1;

						time_t time36 = mktime(&beforetoday36);

						if (difftime(now36, time36) > 7 * 24 * 3600)
						{
							const char* over36 = "###OVERDUE###";

							for (int x = 0;over36[x] != '\0';x++)
							{
								arr36[position36++] = over36[x];
							}
						}

						arr36[position36++] = '\n';
					}
					arr36[position36] = '\0';

					sf::Text admbutton36(font);
					if (arr36[0] == '\0')
					{
						admbutton36.setString("No Unpaid bills found to display");
					}
					else
					{
						admbutton36.setString(arr36);
					}
					admbutton36.setCharacterSize(32);
					admbutton36.setFillColor(sf::Color(255, 140, 0));
					admbutton36.setStyle(sf::Text::Bold);
					admbutton36.setPosition({ 70.f,80.f - scrollOffset });
					window.draw(admbutton36);


				}
				//DISCHARGE PATIENT
				else if (State == 37)
				{
					window.draw(background_Sprite2);
					window.draw(dischargeid37);
					window.draw(dischargebutton37);
					window.draw(dischargebuttontext37);
					dischargebox37.drawscreen(window);
					window.draw(adminresulttext377);
				}
				//VIEW SECURITY LOG
				else if (State == 38)
				{
					window.draw(background_Sprite2);
					ifstream file38("security_log.txt");
					char arr38[5000];
					int count38 = 0;
					if (file38)
					{
						char filetemp38[500];
						while (file38.getline(filetemp38, 200) && count38 < 4900)
						{
							for (int f = 0;filetemp38[f] != '\0';f++)
							{
								arr38[count38++] = filetemp38[f];
							}
							arr38[count38++] = '\n';
						}
						file38.close();
					}
					arr38[count38] = '\0';

					sf::Text admbutton38(font);
					if (arr38[0] == '\0')
					{
						admbutton38.setString("Security log is empty");
					}
					else
					{
						admbutton38.setString(arr38);
					}
					admbutton38.setCharacterSize(32);
					admbutton38.setFillColor(sf::Color(255, 140, 0));
					admbutton38.setStyle(sf::Text::Bold);
					admbutton38.setPosition({ 70.f,80.f - scrollOffset });
					window.draw(admbutton38);
				}
				//GENERATE DAILY REPORT
				else if (State == 39)
				{
					window.draw(background_Sprite2);

					time_t now39 = time(0);
					tm* local39 = localtime(&now39);
					char timearr39[11];
					strftime(timearr39, 11, "%d-%m-%Y", local39);

					int pendingcount39 = 0;
					int completecount39 = 0;
					int	noshowcount39 = 0;
					int cancelcount39 = 0;
					float revenue39 = 0;


					Appointment** admappointsrec = appointments.getall();
					int position39 = appointments.getsize();

					//counting all appointments w.r.t their status
					for (int a = 0; a < position39; a++)
					{
						if (Appointment::Comparechars(admappointsrec[a]->getdate(), timearr39))
						{

							const char* status39 = admappointsrec[a]->getstatus();

							if (Appointment::Comparechars(status39, "pending"))
							{
								pendingcount39++;
							}
							else if (Appointment::Comparechars(status39, "completed"))
							{
								completecount39++;
							}
							else if (Appointment::Comparechars(status39, "no-show"))
							{
								noshowcount39++;
							}
							else if (Appointment::Comparechars(status39, "cancelled"))
							{
								cancelcount39++;
							}
						}

					}

					Bill** admbillrec = bills.getall();
					int billposition39 = bills.getsize();
					//counting total revenue from paid bills on a particular day
					for (int b = 0; b < billposition39; b++)
					{
						if (Appointment::Comparechars(admbillrec[b]->getstatus(), "paid") && Appointment::Comparechars(admbillrec[b]->getdate(), timearr39))
						{
							revenue39 += admbillrec[b]->getamount();
						}
					}
					char arr39[1000];
					int arrindex39 = 0;

					int total39 = pendingcount39 + completecount39 + noshowcount39 + cancelcount39;


					char temparr39[20] = { 0 };
					int temppos39 = 0;


					if (total39 == 0)
					{
						temparr39[temppos39++] = '0';
					}
					else
					{
						char temparr392[20];
						int temppos392 = 0;
						while (total39 > 0)
						{
							temparr392[temppos392++] = total39 % 10 + '0';
							total39 = total39 / 10;
						}
						while (temppos392 > 0)
						{
							temparr39[temppos39++] = temparr392[--temppos392];
						}

					}
					temparr39[temppos39] = '\0';




					char pendingtemparr39[20] = { 0 };
					int pendingtemppos39 = 0;


					if (pendingcount39 == 0)
					{
						pendingtemparr39[pendingtemppos39++] = '0';
					}
					else
					{
						char pendingtemparr392[20];
						int pendingtemppos392 = 0;
						while (pendingcount39 > 0)
						{
							pendingtemparr392[pendingtemppos392++] = pendingcount39 % 10 + '0';
							pendingcount39 = pendingcount39 / 10;
						}
						while (pendingtemppos392 > 0)
						{
							pendingtemparr39[pendingtemppos39++] = pendingtemparr392[--pendingtemppos392];
						}

					}
					pendingtemparr39[pendingtemppos39] = '\0';


					char completetemparr39[20] = { 0 };
					int completetemppos39 = 0;


					if (completecount39 == 0)
					{
						completetemparr39[completetemppos39++] = '0';
					}
					else
					{
						char completetemparr392[20];
						int completetemppos392 = 0;
						while (completecount39 > 0)
						{
							completetemparr392[completetemppos392++] = completecount39 % 10 + '0';
							completecount39 = completecount39 / 10;
						}
						while (completetemppos392 > 0)
						{
							completetemparr39[completetemppos39++] = completetemparr392[--completetemppos392];
						}

					}
					completetemparr39[completetemppos39] = '\0';


					char noshowtemparr39[20] = { 0 };
					int noshowtemppos39 = 0;


					if (noshowcount39 == 0)
					{
						noshowtemparr39[noshowtemppos39++] = '0';
					}
					else
					{
						char noshowtemparr392[20];
						int noshowtemppos392 = 0;
						while (noshowcount39 > 0)
						{
							noshowtemparr392[noshowtemppos392++] = noshowcount39 % 10 + '0';
							noshowcount39 = noshowcount39 / 10;
						}
						while (noshowtemppos392 > 0)
						{
							noshowtemparr39[noshowtemppos39++] = noshowtemparr392[--noshowtemppos392];
						}

					}
					noshowtemparr39[noshowtemppos39] = '\0';

					char canceltemparr39[20] = { 0 };
					int canceltemppos39 = 0;


					if (cancelcount39 == 0)
					{
						canceltemparr39[canceltemppos39++] = '0';
					}
					else
					{
						char canceltemparr392[20];
						int canceltemppos392 = 0;
						while (cancelcount39 > 0)
						{
							canceltemparr392[canceltemppos392++] = cancelcount39 % 10 + '0';
							cancelcount39 = cancelcount39 / 10;
						}
						while (canceltemppos392 > 0)
						{
							canceltemparr39[canceltemppos39++] = canceltemparr392[--canceltemppos392];
						}

					}
					canceltemparr39[canceltemppos39] = '\0';

					const char* patientName39 = "";
					char amountarr39[20] = { 0 };
					for (int b = 0; b < billposition39; b++)
					{
						//displaying patients with unpaid bills
						if (Appointment::Comparechars(admbillrec[b]->getstatus(), "unpaid"))
						{

							int patid39;
							patid39 = admbillrec[b]->getpatid();



							Patient** patientsearch39 = patients.getall();
							int patientcount39 = patients.getsize();

							for (int p = 0; p < patientcount39; p++)
							{
								if (patientsearch39[p] != nullptr && patientsearch39[p]->getId() == patid39)
								{
									patientName39 = patientsearch39[p]->getName();
									break;
								}
							}
							float amount39 = admbillrec[b]->getamount();
							int newamount39 = (int)amount39;
							int amountposition39 = 0;

							if (newamount39 == 0)
							{
								amountarr39[amountposition39++] = '0';
							}
							else
							{
								char tempamountarr39[20];
								int tempamountposition39 = 0;
								while (newamount39 > 0)
								{
									tempamountarr39[tempamountposition39++] = newamount39 % 10 + '0';
									newamount39 = newamount39 / 10;
								}
								while (tempamountposition39 > 0)
								{
									amountarr39[amountposition39++] = tempamountarr39[--tempamountposition39];
								}
							}
							amountarr39[amountposition39] = '\0';
						}
					}














					//adding all these texts to main array for display purpose
					const char* initial391 = "Total appointments today: ";
					const char* initial392 = "Pending: ";
					const char* initial393 = "Completed: ";
					const char* initial394 = "No-Show: ";
					const char* initial395 = "Cancelled: ";
					const char* initial396 = "Revenue collected today: PKR  ";
					const char* initial397 = "Patient Name: ";
					const char* initial398 = "Total Owed: ";
					const char* initial399 = "Doctor Name: ";
					const char* initial3991 = "Doctor Appointment Completed: ";
					const char* initial3992 = "Doctor Appointment Pending: ";
					const char* initial3993 = "Doctor Appointment NoShow: ";










					for (int n = 0; initial391[n] != '\0';n++)
					{
						arr39[arrindex39++] = initial391[n];
					}


					for (int n = 0; temparr39[n] != '\0';n++)
					{
						arr39[arrindex39++] = temparr39[n];
					}
					arr39[arrindex39++] = '\n';

					for (int n = 0; initial392[n] != '\0';n++)
					{
						arr39[arrindex39++] = initial392[n];
					}


					for (int n = 0; pendingtemparr39[n] != '\0';n++)
					{
						arr39[arrindex39++] = pendingtemparr39[n];
					}
					arr39[arrindex39++] = '\n';

					for (int n = 0; initial393[n] != '\0';n++)
					{
						arr39[arrindex39++] = initial393[n];
					}


					for (int n = 0; completetemparr39[n] != '\0';n++)
					{
						arr39[arrindex39++] = completetemparr39[n];
					}
					arr39[arrindex39++] = '\n';

					for (int n = 0; initial394[n] != '\0';n++)
					{
						arr39[arrindex39++] = initial394[n];
					}

					for (int n = 0; noshowtemparr39[n] != '\0';n++)
					{
						arr39[arrindex39++] = noshowtemparr39[n];
					}
					arr39[arrindex39++] = '\n';

					for (int n = 0; initial395[n] != '\0';n++)
					{
						arr39[arrindex39++] = initial395[n];
					}

					for (int n = 0; canceltemparr39[n] != '\0';n++)
					{
						arr39[arrindex39++] = canceltemparr39[n];
					}
					arr39[arrindex39++] = '\n';

					for (int x = 0;initial396[x] != '\0';x++)
					{
						arr39[arrindex39++] = initial396[x];
					}
					int revint39 = (int)revenue39;

					char revtmp39[10];
					int revindex39 = 0;
					char revarray39[20];
					int revarrayindex39 = 0;
					if (revint39 == 0)
					{
						revarray39[revarrayindex39++] = '0';
					}
					else
					{
						while (revint39 > 0)
						{
							revtmp39[revindex39++] = '0' + revint39 % 10;
							revint39 /= 10;
						}
						for (int x = revindex39 - 1;x >= 0;x--)
						{
							revarray39[revarrayindex39++] = revtmp39[x];
						}
					}
					revarray39[revarrayindex39] = '\0';

					for (int n = 0; revarray39[n] != '\0';n++)
					{
						arr39[arrindex39++] = revarray39[n];
					}
					arr39[arrindex39++] = '\n';


					for (int n = 0; initial397[n] != '\0';n++)
					{
						arr39[arrindex39++] = initial397[n];
					}

					for (int n = 0; patientName39[n] != '\0';n++)
					{
						arr39[arrindex39++] = patientName39[n];
					}
					arr39[arrindex39++] = '\n';

					for (int n = 0; initial398[n] != '\0';n++)
					{
						arr39[arrindex39++] = initial398[n];
					}

					for (int n = 0; amountarr39[n] != '\0';n++)
					{
						arr39[arrindex39++] = amountarr39[n];
					}
					arr39[arrindex39++] = '\n';


					Doctor** doctorsearch39 = doctors.getall();
					int doctorcount39 = doctors.getsize();
					//showing doctors and status of all their appintments for current day
					for (int d = 0; d < doctorcount39; d++)
					{
						int dPending39 = 0, dComplete39 = 0, dNoShow39 = 0;
						int docid39 = doctorsearch39[d]->getId();
						const char* doctorName39 = doctorsearch39[d]->getName();

						for (int a = 0; a < position39; a++)
						{
							if (Appointment::Comparechars(admappointsrec[a]->getdate(), timearr39) &&
								admappointsrec[a]->getdocid() == docid39)
							{
								const char* st = admappointsrec[a]->getstatus();
								if (Appointment::Comparechars(st, "completed")) dComplete39++;
								else if (Appointment::Comparechars(st, "pending"))   dPending39++;
								else if (Appointment::Comparechars(st, "no-show"))   dNoShow39++;
							}
						}

						if (dPending39 + dComplete39 + dNoShow39 == 0)
						{
							continue;
						}

						for (int n = 0; initial399[n] != '\0'; n++)
						{
							arr39[arrindex39++] = initial399[n];
						}
						for (int n = 0; doctorName39[n] != '\0'; n++)
						{

							arr39[arrindex39++] = doctorName39[n];
						}
						arr39[arrindex39++] = '\n';

						for (int n = 0; initial3991[n] != '\0'; n++)
						{

							arr39[arrindex39++] = initial3991[n];
						}
						char dctmp[20] = { 0 };
						int dcpos = 0;

						if (dComplete39 == 0)
						{
							dctmp[dcpos++] = '0';
						}
						else
						{
							char r[20];int ri = 0;
							while (dComplete39 > 0)
							{
								r[ri++] = dComplete39 % 10 + '0';
								dComplete39 = dComplete39 / 10;
							}
							while (ri > 0)
							{
								dctmp[dcpos++] = r[--ri];
							}
						}
						dctmp[dcpos] = '\0';

						for (int n = 0;dctmp[n] != '\0';n++)
						{
							arr39[arrindex39++] = dctmp[n];
						}
						arr39[arrindex39++] = '\n';

						for (int n = 0; initial3992[n] != '\0'; n++)
						{
							arr39[arrindex39++] = initial3992[n];
						}
						char dptmp[20] = { 0 };
						int dppos = 0;

						if (dPending39 == 0)
						{
							dptmp[dppos++] = '0';
						}
						else
						{
							char r[20];int ri = 0;
							while (dPending39 > 0)
							{
								r[ri++] = dPending39 % 10 + '0';
								dPending39 = dPending39 / 10;
							}
							while (ri > 0)
							{
								dptmp[dppos++] = r[--ri];
							}
						}
						dptmp[dppos] = '\0';

						for (int n = 0;dptmp[n] != '\0';n++)
						{
							arr39[arrindex39++] = dptmp[n];
						}
						arr39[arrindex39++] = '\n';

						for (int n = 0; initial3993[n] != '\0'; n++)

						{
							arr39[arrindex39++] = initial3993[n];
						}
						char dntmp[20] = { 0 };
						int dnpos = 0;

						if (dNoShow39 == 0)
						{
							dntmp[dnpos++] = '0';
						}
						else
						{
							char r[20];
							int ri = 0;
							while (dNoShow39 > 0)
							{
								r[ri++] = dNoShow39 % 10 + '0';
								dNoShow39 = dNoShow39 / 10;
							}
							while (ri > 0)
							{
								dntmp[dnpos++] = r[--ri];
							}
						}
						dntmp[dnpos] = '\0';

						for (int n = 0;dntmp[n] != '\0';n++)
						{
							arr39[arrindex39++] = dntmp[n];
						}
						arr39[arrindex39++] = '\n';
						arr39[arrindex39++] = '\n';
					}
					arr39[arrindex39] = '\0';

					sf::Text adminbutton39(font);
					adminbutton39.setString(arr39);
					adminbutton39.setCharacterSize(32);
					adminbutton39.setFillColor(sf::Color(255, 140, 0));
					adminbutton39.setStyle(sf::Text::Bold);
					adminbutton39.setPosition({ 70.f, 80.f - scrollOffset });
					window.draw(adminbutton39);
				}

				window.display();
	}
}
