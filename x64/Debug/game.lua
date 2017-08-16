logTimer = 0.0
consoleTimer = 0.0

function Start()
	Engine.Core.Initialise(1024, 768, false, "D3D11");
	Engine.Core.SetMaxFPS(60);
	Engine.Core.PrintSystemInfo();
end

function Update(dt)
	logTimer = logTimer + dt;
	consoleTimer = consoleTimer + dt;
	
	-- Set window title.
	if (consoleTimer > 0.2)
	then
		Engine.Console.SetTitle(string.format("Engine - CPU: %.2f FPS", 1.0 / dt));
		consoleTimer = consoleTimer - 0.2;
	end
	
	if (logTimer > 2.0)
	then
		--timeStr = string.format("time: %f", 1 / dt);
		--Engine.Logger.Log(timeStr);
		logTimer = logTimer - 2.0;
	end
end

function Draw()
end

function Destroy()
	Engine.Logger.Log("Goodbye.");
end
