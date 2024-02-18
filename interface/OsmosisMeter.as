import gfx.io.GameDelegate;
import gfx.managers.FocusHandler;
import gfx.ui.InputDetails;
import gfx.ui.NavigationCode;
import Shared.GlobalFunc;
import Components.Meter;
import skyui.util.Tween;
import mx.utils.Delegate;
import com.greensock.TimelineLite;
import com.greensock.easing.*;

class OsmosisMeter extends MovieClip
{
	var MeterContainer:MovieClip;
	var FlashMeter:MovieClip;
	
	var meterDuration:Number;
	var minWidth:Number;
	var maxWidth:Number;
	var Percent:Number;

	var targetPercent:Number;

	var MeterTimeline:TimelineLite;
	var FlashTimeline:TimelineLite;
	var FaderTimeline:TimelineLite;
	
	var MeterContainerBarColor:Color;
	var MeterContainerBarBGColor:Color;
	var FlashMeterColor:Color;
	var FlashMeterColorTransform:Object;
	
	var MenuEnabled:Boolean = false;
	
	function OsmosisMeter()
	{
		super();
		targetPercent = 0;
		meterDuration = 0.01;
		MeterTimeline = new TimelineLite({paused:true});
		//FlashTimeline = new TimelineLite({paused:true, onUpdate:setTransformOnUpdate, onUpdateScope:this, onComplete:doFlash, onCompleteScope:this});
		FlashTimeline = new TimelineLite({paused:true, onUpdate:setTransformOnUpdate, onUpdateScope:this});
		FaderTimeline = new TimelineLite({paused:true});
		
		
		MeterContainerBarColor = new Color(MeterContainer.Bar.BarColour);
		MeterContainerBarBGColor = new Color(MeterContainer.BarBG);
		FlashMeterColor = new Color(FlashMeter);
		setBarAndFlashColor(0xc076e8, 0xc076e8);

		
		FlashMeterColorTransform = { aa: 100, ab: -255 }
		FlashMeterColor.setTransform(FlashMeterColorTransform);
		
		maxWidth = MeterContainer.Mask._x;
		minWidth = MeterContainer.Mask._x - MeterContainer.Mask._width;
		Percent = (maxWidth - minWidth) / 100;
		
	}
	
	function onLoad(): Void
	{
		//setLocation(960, 960, 0, 150, 150);
		doHide();
		//doShow();
		//setBarAndFlashColor(0xc076e8, 0xc076e8);
		//doFadeOut();
		//doFadeOut();
		//doFlash();
		//updateMeterPercent(0);
		//this.setMeterPercent(0);
		
	}
	

	public function setLocation(xpos: Number, ypos: Number, rot: Number, xscale: Number, yscale: Number): Void
	{
		this._x = xpos;
		this._y = ypos;
		this._rotation = rot;
		this._xscale = xscale;
		this._yscale = yscale;
	}
	
	public function setBarAndFlashColor(newBarColor: Number, newFlashColor: Number ): Void
	{
		MeterContainerBarColor.setRGB(newBarColor);
		MeterContainerBarBGColor.setRGB(newBarColor);
		FlashMeterColor.setRGB(newFlashColor);
	}
	
	public function doFadeOut(): Void
	{
		FaderTimeline.to(this, 1, {ease: Power1.easeOut, _alpha: 0});
		FaderTimeline.play();
	}
	
	public function doHide(): Void
	{
		this._visible = false;
	}
		
	public function doShow(): Void
	{
		this._visible = true;
		this._alpha = 100;
	}
	
	public function doFlash(): Void
	{
		if (!FlashTimeline.isActive()){
			FlashTimeline.to(FlashMeterColorTransform, 0.4, {ease: Power1.easeIn, ab: 0});
			FlashTimeline.to(FlashMeterColorTransform, 0.3, {ease: Power1.easeOut, ab: -255});
			FlashTimeline.play();
		}
	}
	
	// called onUpdate of FlashTimeline, to apply the ColorTransform alpha tween.
	function setTransformOnUpdate(){
		FlashMeterColor.setTransform(FlashMeterColorTransform);
	}
	
	
	public function setMeterPercent(CurrentPercent:Number):Void
	{
		MeterTimeline.clear();
		CurrentPercent = doValueClamp(CurrentPercent);
		MeterContainer.Mask._x = minWidth + (Percent * CurrentPercent);
	}

	public function doValueClamp(clampValue:Number):Number
	{
		return clampValue > 100 ? 100 : (clampValue <= 0 ? -1 : clampValue);
	}

	public function updateMeterPercent(CurrentPercent:Number):Void
	{
		CurrentPercent = doValueClamp(CurrentPercent);

		if (!MeterTimeline.isActive())
		{
			MeterTimeline.clear();
			MeterTimeline.progress(0);
			MeterTimeline.restart();
		}
		MeterTimeline.to(MeterContainer.Mask,1,{_x:minWidth +(Percent * CurrentPercent)},MeterTimeline.time() + meterDuration);
		MeterTimeline.play();
	}
}