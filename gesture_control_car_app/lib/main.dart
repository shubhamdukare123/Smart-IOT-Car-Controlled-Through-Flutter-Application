import "package:flutter/material.dart";

void main() {
  runApp(const CarApp());
}

class CarApp extends StatelessWidget {
  const CarApp({super.key});

  @override 
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: CarAppUI(),
    );
  }
}

class CarAppUI extends StatefulWidget {
  const CarAppUI({super.key});

  @override 
  State createState() => _CarAppUIState();
}

class _CarAppUIState extends State {

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Colors.blue,
        title: const Text("Car App",
          style: TextStyle(
            fontSize: 25,
            fontWeight: FontWeight.w600,
          ),
        )
      ),

      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.center,
        children : [
          ElevatedButton(
            onPressed: (){},
            child: const Text("Forward",
              style: TextStyle(
                fontSize: 25,
                fontWeight: FontWeight.w400
              ),
            )
           ),

           const SizedBox(height: 50),

             ElevatedButton(
            onPressed: (){},
            child: const Text("Reverse",
              style: TextStyle(
                fontSize: 25,
                fontWeight: FontWeight.w400
              ),
            )
           ),

           const SizedBox(height: 50),

  ElevatedButton(
            onPressed: (){},
            child: const Text("Left",
              style: TextStyle(
                fontSize: 25,
                fontWeight: FontWeight.w400
              ),
            )
           ),

           const SizedBox(height: 50),


  ElevatedButton(
            onPressed: (){},
            child: const Text("Right",
              style: TextStyle(
                fontSize: 25,
                fontWeight: FontWeight.w400
              ),
            )
           ),

           const SizedBox(height: 50),



        ],
      ),
    );
  }

}