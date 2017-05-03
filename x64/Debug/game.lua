function Start()
	Engine.Core.Initialise(1024, 768, true);
	Engine.Core.SetMaxFPS(60);
	Engine.Core.PrintSystemInfo();
	
	Engine.Logger.LogWarning("Warning!");
end

function Update()
	dt = string.format("time: %.2f", Engine.Time.DeltaTime());
	Engine.Logger.Log(dt);
end

function Draw()
end

function Destroy()
end
