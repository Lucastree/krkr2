//
// $Id$
//



#include "ncbind.hpp"

///----------------------------------------------------------------------
/// 変数
tjs_uint32 timeHint, typeHint ,timeLineFrameWidthHint, timelineFrameHeightHint,_singleFrameColorHint, _tweenFrameColorHint, _continuousFrameColorHint, fillRectHint, winDarken2Hint, winDarken1Hint, winLighten1Hint, winWhiteHint, canvasHint, fontHeightHint, getTextWidthHint, drawTextHint, frameListHint, drawFrameHint, selectionHint, colorRectHint, layerHint, topHint, oneSecondFrameBgLayerHint, halfSecondFrameBgLayerHint, fifthFrameBgLayerHint, normalFrameBgLayerHint, copyRectHint, operateRectHint, widthHint, heightHint, frameTopMarkerLayerHint, dashLineAppHint, drawLineHint, fontHint, rootHint, ownerHint, framePerSecondHint;
;

enum {
  TIMELINE_FRAME_TYPE_NULL = 0,
  TIMELINE_FRAME_TYPE_SINGLE = 1,
  TIMELINE_FRAME_TYPE_CONTINUOUS = 2,
  TIMELINE_FRAME_TYPE_TWEEN = 3,
};

///----------------------------------------------------------------------
/// フレームを検索する
tjs_int timeline_find_frame(tTJSVariant frameList, tjs_int time, bool includeTail)
{
  ncbPropAccessor frameListObj(frameList);

  tjs_int begin, end, mid;

  begin = 0;
  end = frameListObj.GetArrayCount();

  // 末尾だけ特殊処理
  if (end) {
    tTJSVariant lastFrame = frameListObj.GetValue(end - 1, ncbTypedefs::Tag<tTJSVariant>());
    ncbPropAccessor lastFrameObj(lastFrame);
    tjs_int lastTime = lastFrameObj.GetValue(L"time", ncbTypedefs::Tag<tjs_int>(), 0, &timeHint);

    if (! includeTail) {
      if (lastTime == time)
	return end - 1;
      if (lastTime < time)
	return -1;
    } else {
      if (lastTime <= time)
	return end - 1;
    }
  }
  
  // 二分検索
  while (begin < end) {
    mid = tjs_int((begin + end) / 2);

    tTJSVariant curFrame = frameListObj.GetValue(mid, ncbTypedefs::Tag<tTJSVariant>());
    ncbPropAccessor curFrameObj(curFrame);
    tjs_int curTime = curFrameObj.GetValue(L"time", ncbTypedefs::Tag<tjs_int>(), 0, &timeHint);

    if (curTime <= time) {
      tTJSVariant nextFrame = frameListObj.GetValue(mid + 1, ncbTypedefs::Tag<tTJSVariant>());
      ncbPropAccessor nextFrameObj(nextFrame);
      tjs_int nextTime = nextFrameObj.GetValue(L"time", ncbTypedefs::Tag<tjs_int>(), 0, &timeHint);
      if (time < nextTime)
	return mid;
    }
    if (time < curTime)
      end = mid;
    else
      begin = mid + 1;
  }

  return -1;
}


///----------------------------------------------------------------------
/// BGを描画する
void timeline_draw_bg(tTJSVariant item, tTJSVariant view, tjs_int y, tjs_int fromTime, tjs_int toTime)
{
  ncbPropAccessor itemObj(item);
  ncbPropAccessor viewObj(view);

  ncbPropAccessor rootObj(itemObj.GetValue(L"root", ncbTypedefs::Tag<tTJSVariant>(), 0, &rootHint));
  ncbPropAccessor ownerObj(rootObj.GetValue(L"owner", ncbTypedefs::Tag<tTJSVariant>(), 0, &ownerHint));
  tjs_int fps = ownerObj.GetValue(L"framePerSecond", ncbTypedefs::Tag<tjs_int>(), 0 ,&framePerSecondHint);

  iTJSDispatch2 *global = TVPGetScriptDispatch();
  ncbPropAccessor globalObj(global);
  global->Release();

  tjs_int TIMELINE_FRAME_WIDTH = itemObj.GetValue(L"TIMELINE_FRAME_WIDTH", ncbTypedefs::Tag<tjs_int>(), 0, &timeLineFrameWidthHint);
  tjs_int TIMELINE_FRAME_HEIGHT = globalObj.GetValue(L"TIMELINE_FRAME_HEIGHT", ncbTypedefs::Tag<tjs_int>(), 0, &timelineFrameHeightHint);

  tTJSVariant oneSecondFrameBgLayer, halfSecondFrameBgLayer, fifthFrameBgLayer, normalFrameBgLayer;

  // バックグラウンドを描画
  for (tjs_int time = fromTime; time < toTime; time ++) {
    tjs_int x = time * TIMELINE_FRAME_WIDTH;
    tTJSVariant layer;
    if (time % fps == 0) {
      if (oneSecondFrameBgLayer.Type() == tvtVoid)
        oneSecondFrameBgLayer = viewObj.GetValue(L"oneSecondFrameBgLayer", ncbTypedefs::Tag<tTJSVariant>(), 0, &oneSecondFrameBgLayerHint);
      layer = oneSecondFrameBgLayer;
    } else if (time % fps * 2 == fps) {
      if (halfSecondFrameBgLayer.Type() == tvtVoid)
        halfSecondFrameBgLayer = viewObj.GetValue(L"halfSecondFrameBgLayer", ncbTypedefs::Tag<tTJSVariant>(), 0, &halfSecondFrameBgLayerHint);
      layer = halfSecondFrameBgLayer;
    } else if (time % 5 == 0) {
      if (fifthFrameBgLayer.Type() == tvtVoid)
        fifthFrameBgLayer = viewObj.GetValue(L"fifthFrameBgLayer", ncbTypedefs::Tag<tTJSVariant>(), 0, &fifthFrameBgLayerHint);
      layer = fifthFrameBgLayer;
    } else {
      if (normalFrameBgLayer.Type() == tvtVoid)
        normalFrameBgLayer = viewObj.GetValue(L"normalFrameBgLayer", ncbTypedefs::Tag<tTJSVariant>(), 0, &normalFrameBgLayerHint);
      layer = normalFrameBgLayer;
    }
    viewObj.FuncCall(0, L"copyRect", &copyRectHint, NULL,
                     x, y, layer, 0, 0, TIMELINE_FRAME_WIDTH, TIMELINE_FRAME_HEIGHT);
  }
}

///----------------------------------------------------------------------
/// フレームを描画する
void timeline_draw_frame(tTJSVariant item, tTJSVariant view, tjs_int y, tTJSVariant frame, tjs_int length)
{
  ncbPropAccessor itemObj(item);
  ncbPropAccessor viewObj(view);
  ncbPropAccessor frameObj(frame);

  iTJSDispatch2 *global = TVPGetScriptDispatch();
  ncbPropAccessor globalObj(global);
  global->Release();

  tjs_int WIN_DARKEN2 = globalObj.GetValue(L"WIN_DARKEN2", ncbTypedefs::Tag<tjs_uint>(), 0, &winDarken2Hint);
  tjs_int TIMELINE_FRAME_WIDTH = itemObj.GetValue(L"TIMELINE_FRAME_WIDTH", ncbTypedefs::Tag<tjs_int>(), 0, &timeLineFrameWidthHint);
  tjs_int TIMELINE_FRAME_HEIGHT = globalObj.GetValue(L"TIMELINE_FRAME_HEIGHT", ncbTypedefs::Tag<tjs_int>(), 0, &timelineFrameHeightHint);
  tjs_int frameType = frameObj.GetValue(L"type", ncbTypedefs::Tag<tjs_int>(), 0, &typeHint);
  tjs_int frameTime = frameObj.GetValue(L"time", ncbTypedefs::Tag<tjs_int>(), 0, &timeHint);

  switch (frameType) {
  case TIMELINE_FRAME_TYPE_NULL:
    timeline_draw_bg(item, view, y, frameTime, frameTime + length);
    return;
  case TIMELINE_FRAME_TYPE_SINGLE: {

    timeline_draw_bg(item, view, y, frameTime + 1, frameTime + length);
    tjs_int singleFrameColor  = itemObj.GetValue(L"_singleFrameColor", ncbTypedefs::Tag<tjs_int>(), 0, &_singleFrameColorHint);
    singleFrameColor |= 0xFF000000;
    viewObj.FuncCall(0, L"fillRect", &fillRectHint, NULL, 
		     frameTime * TIMELINE_FRAME_WIDTH, y, TIMELINE_FRAME_WIDTH - 1, TIMELINE_FRAME_HEIGHT - 1, singleFrameColor);
    return;
  }
  case TIMELINE_FRAME_TYPE_CONTINUOUS:
  case TIMELINE_FRAME_TYPE_TWEEN: {
    tjs_int color;
    if (frameType == TIMELINE_FRAME_TYPE_CONTINUOUS)
      color = itemObj.GetValue(L"_continuousFrameColor", ncbTypedefs::Tag<tjs_int>(), 0, &_continuousFrameColorHint);
    else
      color = itemObj.GetValue(L"_tweenFrameColor", ncbTypedefs::Tag<tjs_int>(), 0, &_tweenFrameColorHint);
    color |= 0xFF000000;
    // BG描画
    viewObj.FuncCall(0, L"fillRect", &fillRectHint, NULL,
		     (frameTime + length) * TIMELINE_FRAME_WIDTH - 1, y, 1, TIMELINE_FRAME_HEIGHT, WIN_DARKEN2);
    viewObj.FuncCall(0, L"fillRect", &fillRectHint, NULL,
		     frameTime * TIMELINE_FRAME_WIDTH, y + TIMELINE_FRAME_HEIGHT - 1, length * TIMELINE_FRAME_WIDTH, 1, WIN_DARKEN2);
    viewObj.FuncCall(0, L"fillRect", &fillRectHint, NULL,
		     frameTime * TIMELINE_FRAME_WIDTH, y,
		     length * TIMELINE_FRAME_WIDTH - 1,
		     TIMELINE_FRAME_HEIGHT - 1,
		     color);
    // 左マーカー描画
    tTJSVariant frameTopMarkerLayer = viewObj.GetValue(L"frameTopMarkerLayer", ncbTypedefs::Tag<tTJSVariant>(), 0, &frameTopMarkerLayerHint);
    ncbPropAccessor frameTopMarkerLayerObj(frameTopMarkerLayer);
    tjs_int mw = frameTopMarkerLayerObj.GetValue(L"width", ncbTypedefs::Tag<tjs_int>(), 0, &widthHint);
    tjs_int mh = frameTopMarkerLayerObj.GetValue(L"height", ncbTypedefs::Tag<tjs_int>(), 0, &heightHint);
    viewObj.FuncCall(0, L"operateRect", &operateRectHint, NULL,
                     frameTime * TIMELINE_FRAME_WIDTH, y, 
                     frameTopMarkerLayer, 0, 0, mw, mh);
    // 右マーカー描画
    //      for (var i = 0; i < cw; i++) 
    //        view.fillRect((frame.time + length) * TIMELINE_FRAME_WIDTH - 4 - i, y + (TIMELINE_FRAME_HEIGHT - (cw - i * 2)) / 2, 1, cw - i * 2, WIN_DARKEN2);
    // トゥイーンの破線描画
    if (frameType == TIMELINE_FRAME_TYPE_TWEEN) {
      tTJSVariant dashLineApp = viewObj.GetValue(L"dashLineApp", ncbTypedefs::Tag<tTJSVariant>(), 0, &dashLineAppHint);
      if (dashLineApp.Type() != tvtVoid) {
        viewObj.FuncCall(0, L"drawLine", &drawLineHint, NULL,
                         dashLineApp, (frameTime + 1) * TIMELINE_FRAME_WIDTH, y + TIMELINE_FRAME_HEIGHT / 2 - 1, (frameTime + length) * TIMELINE_FRAME_WIDTH, y + TIMELINE_FRAME_HEIGHT / 2 - 1);
      } else {
        for (tjs_int i = frameTime + 1; i < frameTime + length; i++) {
          viewObj.FuncCall(0, L"fillRect", &fillRectHint, NULL,
                           i * TIMELINE_FRAME_WIDTH, y + TIMELINE_FRAME_HEIGHT / 2 - 1, TIMELINE_FRAME_WIDTH / 2 - 2, 1, WIN_DARKEN2);
          viewObj.FuncCall(0, L"fillRect", &fillRectHint, NULL,
                           i * TIMELINE_FRAME_WIDTH + TIMELINE_FRAME_WIDTH / 2, y + TIMELINE_FRAME_HEIGHT / 2 - 1, TIMELINE_FRAME_WIDTH / 2 - 2, 1, WIN_DARKEN2);
        }
      }
    }
    // フレーム数描画
    if (length > 2) {
      tTJSVariant canvas = viewObj.GetValue(L"canvas", ncbTypedefs::Tag<tTJSVariant>(), 0, &canvasHint);
      ncbPropAccessor canvasObj(canvas);
      tjs_int fontHeight = TIMELINE_FRAME_HEIGHT - 4;
      canvasObj.SetValue(L"fontHeight", fontHeight, 0, &fontHeightHint);
      ttstr text(length);
      tTJSVariant textWidth;
      tTJSVariant font = canvasObj.GetValue(L"font", ncbTypedefs::Tag<tTJSVariant>(), 0, &fontHint);
      ncbPropAccessor fontObj(font);
      fontObj.FuncCall(0, L"getTextWidth", &getTextWidthHint, &textWidth,
                       text);
      tjs_int l = frameTime * TIMELINE_FRAME_WIDTH + ((length * TIMELINE_FRAME_WIDTH) - tjs_int(textWidth)) / 2;
      tjs_int t = y + int((TIMELINE_FRAME_HEIGHT - fontHeight) / 2) - 1;
      viewObj.FuncCall(0, L"fillRect", &fillRectHint, NULL,
		       l - 1, t - 1, tjs_int(textWidth) + 2, fontHeight + 2, color);
      viewObj.FuncCall(0, L"drawText", &drawTextHint, NULL,
		       l, t, text, tjs_int(WIN_DARKEN2 & 0xFFFFFF));
    }
    return;
  }
  }
}

///----------------------------------------------------------------------
// タイムラインを描画する
void timeline_draw_timeline(tTJSVariant item, tTJSVariant view, tjs_int fromTime, tjs_int toTime) 
{
  ncbPropAccessor itemObj(item);
  ncbPropAccessor viewObj(view);
  tTJSVariant layer = itemObj.GetValue(L"layer", ncbTypedefs::Tag<tTJSVariant>(), 0, &layerHint);
  ncbPropAccessor layerObj(layer);

  iTJSDispatch2 *global = TVPGetScriptDispatch();
  ncbPropAccessor globalObj(global);
  global->Release();

  tjs_int y = layerObj.GetValue(L"top", ncbTypedefs::Tag<tjs_int>(), 0, &topHint);
  tTJSVariant frameList = itemObj.GetValue(L"frameList", ncbTypedefs::Tag<tTJSVariant>(), 0, &frameListHint);
  ncbPropAccessor frameListObj(frameList);
  tjs_int frameListCount = frameListObj.GetArrayCount();

  // 描画範囲を確定
  tjs_int fromFrame = timeline_find_frame(frameList, fromTime, true);
  tjs_int toFrame = timeline_find_frame(frameList, toTime, true);

  // バックグラウンドを描画
  if (fromFrame < 0 && toFrame < 0) {
    timeline_draw_bg(item, view, y, fromTime, toTime);
  } else {
    if (fromFrame < 0) 
      timeline_draw_bg(item, view, y, fromTime, ncbPropAccessor(frameListObj.GetValue(0, ncbTypedefs::Tag<tTJSVariant>())).GetValue(L"time", ncbTypedefs::Tag<tjs_int>(), 0, &timeHint));
    if (toFrame == frameListCount - 1) 
      timeline_draw_bg(item, view, y, ncbPropAccessor(frameListObj.GetValue(-1, ncbTypedefs::Tag<tTJSVariant>())).GetValue(L"time", ncbTypedefs::Tag<tjs_int>(), 0, &timeHint), toTime);
  }

  // フレームを描画
  for (tjs_int i = fromFrame; i <= toFrame; i++) {
    if (i == -1)
      continue;
    tTJSVariant frame = frameListObj.GetValue(i, ncbTypedefs::Tag<tTJSVariant>());
    ncbPropAccessor frameObj(frame);
    tjs_int headTime, tailTime;
    headTime = frameObj.GetValue(L"time", ncbTypedefs::Tag<tjs_int>(), 0, &timeHint);
    if (i < frameListCount - 1) {
      tTJSVariant nextFrame = frameListObj.GetValue(i + 1, ncbTypedefs::Tag<tTJSVariant>());
      ncbPropAccessor nextFrameObj(nextFrame);
      tailTime = nextFrameObj.GetValue(L"time", ncbTypedefs::Tag<tjs_int>(), 0, &timeHint);
    } else 
      tailTime = headTime;
    if (! (tailTime < fromTime
	   || headTime > toTime)) {
      itemObj.FuncCall(0, L"drawFrame", &drawFrameHint, NULL,
		       view, y, frame, tailTime - headTime);
    }
  }
  // 選択範囲描画
  tTJSVariant selection = itemObj.GetValue(L"selection", ncbTypedefs::Tag<tTJSVariant>(), 0, &selectionHint);
  if (selection.Type() != tvtVoid) {
    tjs_int TIMELINE_FRAME_WIDTH = itemObj.GetValue(L"TIMELINE_FRAME_WIDTH", ncbTypedefs::Tag<tjs_int>(), 0, &timeLineFrameWidthHint);
    tjs_int TIMELINE_FRAME_HEIGHT = globalObj.GetValue(L"TIMELINE_FRAME_HEIGHT", ncbTypedefs::Tag<tjs_int>(), 0, &timelineFrameHeightHint);

    ncbPropAccessor selectionObj(selection);
    viewObj.FuncCall(0, L"colorRect", &colorRectHint, NULL,
		     selectionObj.getIntValue(0) * TIMELINE_FRAME_WIDTH, y, (selectionObj.getIntValue(1) - selectionObj.getIntValue(0)) * TIMELINE_FRAME_WIDTH, TIMELINE_FRAME_HEIGHT, selectionObj.getIntValue(2) ? 0xFF0000 : 0, 128);
  }
}

//----------------------------------------------------------------------
// バインド
NCB_REGISTER_FUNCTION(timeline_find_frame, timeline_find_frame);
NCB_REGISTER_FUNCTION(timeline_draw_bg, timeline_draw_bg);
NCB_REGISTER_FUNCTION(timeline_draw_frame, timeline_draw_frame);
NCB_REGISTER_FUNCTION(timeline_draw_timeline, timeline_draw_timeline);
