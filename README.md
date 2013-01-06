<<<<<<< HEAD
  


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>colorOfMind/README.md at master · sinlab-semester-2012/colorOfMind</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon-precomposed" sizes="57x57" href="apple-touch-icon-114.png" />
    <link rel="apple-touch-icon-precomposed" sizes="114x114" href="apple-touch-icon-114.png" />
    <link rel="apple-touch-icon-precomposed" sizes="72x72" href="apple-touch-icon-144.png" />
    <link rel="apple-touch-icon-precomposed" sizes="144x144" href="apple-touch-icon-144.png" />
    <meta name="msapplication-TileImage" content="/windows-tile.png">
    <meta name="msapplication-TileColor" content="#ffffff">
=======
##colorOfMind - A brain computer guided environment


The purpose of this program is to map the state of mind of the user using the Emotiv EPOC headset with a RGB spot light.
The project is using the Emokit driver to get raw packets from the device and FFTW to process the signal.

For more infos:  
*The project, please check the wiki : https://github.com/sinlab-semester-2012/colorOfMind/wiki  
*Emotiv EPOC : http://en.wikipedia.org/wiki/Emotiv_Systems#Emotiv_EPOC  
*SINLAB : http://www.sinlab.ch/  
>>>>>>> b4da2f5b624d22b10833c65651540d60965c62aa

    
    
    <link rel="icon" type="image/x-icon" href="/favicon.ico" />

<<<<<<< HEAD
    <meta content="authenticity_token" name="csrf-param" />
<meta content="wTZKI3e5lSPJm6yafZGI52m+18gQyzTtXn2w7xT72ow=" name="csrf-token" />

    <link href="https://a248.e.akamai.net/assets.github.com/assets/github-8fe1e4a1e0551ad89f1b244e4b6de8214880aaf1.css" media="screen" rel="stylesheet" type="text/css" />
    <link href="https://a248.e.akamai.net/assets.github.com/assets/github2-6453311924e72881f7fc04c5f431847ef213901b.css" media="screen" rel="stylesheet" type="text/css" />
    
=======
##Required Libraries
==================

###Emokit  
*CMake - http://www.cmake.org  
*libmcrypt - https://sourceforge.net/projects/mcrypt/  
*hidapi - http://www.signal11.us/oss/hidapi/  
>>>>>>> b4da2f5b624d22b10833c65651540d60965c62aa

###Signal Processing
*FFTW 3.3 - http://www.fftw.org/download.html  

<<<<<<< HEAD
    <script src="https://a248.e.akamai.net/assets.github.com/assets/frameworks-971f385ccf2fcbf04f87e9ffca82e855620eb233.js" type="text/javascript"></script>
    <script src="https://a248.e.akamai.net/assets.github.com/assets/github-7f9cff56713bf383147d4e2aca4f8a9b7c9720b0.js" type="text/javascript"></script>
    

        <link rel='permalink' href='/sinlab-semester-2012/colorOfMind/blob/b4da2f5b624d22b10833c65651540d60965c62aa/README.md'>
    <meta property="og:title" content="colorOfMind"/>
    <meta property="og:type" content="githubog:gitrepository"/>
    <meta property="og:url" content="https://github.com/sinlab-semester-2012/colorOfMind"/>
    <meta property="og:image" content="https://secure.gravatar.com/avatar/bd0cc000a21974697a24aa2cc928faa2?s=420&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png"/>
    <meta property="og:site_name" content="GitHub"/>
    <meta property="og:description" content=" a brain computer guided environment. Contribute to colorOfMind development by creating an account on GitHub."/>
=======
###Dmx (optional)
*oscpack - Modified version already included in colorOfMind  
*Processing - http://processing.org/  
*DMXP512 - http://motscousus.com/stuff/2011-01_dmxP512/  

###Plot (optional)
*Gnuplot - http://www.gnuplot.info/faq/faq.html
>>>>>>> b4da2f5b624d22b10833c65651540d60965c62aa

    <meta name="description" content=" a brain computer guided environment. Contribute to colorOfMind development by creating an account on GitHub." />

<<<<<<< HEAD
  <link href="https://github.com/sinlab-semester-2012/colorOfMind/commits/master.atom" rel="alternate" title="Recent Commits to colorOfMind:master" type="application/atom+xml" />

  </head>

=======
##Install

###Linux
Install the dependencies  
Follow the guide to install the depedencies if needed : https://github.com/sinlab-semester-2012/colorOfMind/wiki/How-to-Install-%3F

Use the build.sh script and then the example you want :
"./bin/emotiv" to get the datas from the headset or a file  
"./bin/contact" to get the real-time value of the sensors  
"./bin/lightShow" to start the light show  

###Windows :
Install the dependencies
Build the program using the cmake command
Should work not tested yet

##Platform Specifics Issues
=========================
>>>>>>> b4da2f5b624d22b10833c65651540d60965c62aa

  <body class="logged_in page-blob linux vis-public env-production ">
    <div id="wrapper">

<<<<<<< HEAD
      

      

      


        <div class="header header-logged-in true">
          <div class="container clearfix">

            <a class="header-logo-blacktocat" href="https://github.com/">
  <span class="mega-icon mega-icon-blacktocat"></span>
</a>

            <div class="divider-vertical"></div>

              <a href="/notifications" class="notification-indicator tooltipped downwards" title="You have no unread notifications">
    <span class="mail-status all-read"></span>
  </a>
  <div class="divider-vertical"></div>


              
  <div class="topsearch command-bar-activated">
    <form accept-charset="UTF-8" action="/search" class="command_bar_form" id="top_search_form" method="get">
  <a href="/search/advanced" class="advanced-search tooltipped downwards command-bar-search" id="advanced_search" title="Advanced search"><span class="mini-icon mini-icon-advanced-search "></span></a>

  <input type="text" name="q" id="command-bar" placeholder="Search or type a command" tabindex="1" data-username="sinlab-semester-2012" autocapitalize="off">

  <span class="mini-icon help tooltipped downwards" title="Show command bar help">
    <span class="mini-icon mini-icon-help"></span>
  </span>

  <input type="hidden" name="ref" value="commandbar">

  <div class="divider-vertical"></div>
</form>



    <ul class="top-nav">
        <li class="explore"><a href="https://github.com/explore">Explore</a></li>
        <li><a href="https://gist.github.com">Gist</a></li>
        <li><a href="/blog">Blog</a></li>
      <li><a href="http://help.github.com">Help</a></li>
    </ul>
  </div>


            

  
    <ul id="user-links">
      <li>
        <a href="https://github.com/sinlab-semester-2012" class="name">
          <img height="20" src="https://secure.gravatar.com/avatar/bd0cc000a21974697a24aa2cc928faa2?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /> sinlab-semester-2012
        </a>
      </li>
      <li>
        <a href="/new" id="new_repo" class="tooltipped downwards" title="Create a new repo">
          <span class="mini-icon mini-icon-create"></span>
        </a>
      </li>
      <li>
        <a href="/settings/profile" id="account_settings"
          class="tooltipped downwards"
          title="Account settings ">
          <span class="mini-icon mini-icon-account-settings"></span>
        </a>
      </li>
      <li>
          <a href="/logout" data-method="post" id="logout" class="tooltipped downwards" title="Sign out">
            <span class="mini-icon mini-icon-logout"></span>
          </a>
      </li>
    </ul>



            
          </div>
        </div>


      

      


            <div class="site hfeed" itemscope itemtype="http://schema.org/WebPage">
      <div class="hentry">
        
        <div class="pagehead repohead instapaper_ignore readability-menu">
          <div class="container">
            <div class="title-actions-bar">
              


                  <ul class="pagehead-actions">
          <li class="nspr">
            <a href="/sinlab-semester-2012/colorOfMind/pull/new/master" class="minibutton btn-pull-request" icon_class="mini-icon-pull-request"><span class="mini-icon mini-icon-pull-request"></span>Pull Request</a>
          </li>

          <li class="subscription">
              <form accept-charset="UTF-8" action="/notifications/subscribe" data-autosubmit="true" data-remote="true" method="post"><div style="margin:0;padding:0;display:inline"><input name="authenticity_token" type="hidden" value="wTZKI3e5lSPJm6yafZGI52m+18gQyzTtXn2w7xT72ow=" /></div>  <input id="repository_id" name="repository_id" type="hidden" value="6030918" />
  <div class="context-menu-container js-menu-container js-context-menu">
    <span class="minibutton switcher bigger js-menu-target">
      <span class="js-context-button">
          <span class="mini-icon mini-icon-watching"></span>Watch
      </span>
    </span>

    <div class="context-pane js-menu-content">
      <a href="#" class="close js-menu-close"><span class="mini-icon mini-icon-remove-close"></span></a>
      <div class="context-title">Notification status</div>

      <div class="context-body pane-selector">
        <ul class="js-navigation-container">
          <li class="selector-item js-navigation-item js-navigation-target selected">
            <span class="mini-icon mini-icon-confirm"></span>
            <label>
              <input checked="checked" id="do_included" name="do" type="radio" value="included" />
              <h4>Not watching</h4>
              <p>You will only receive notifications when you participate or are mentioned.</p>
            </label>
            <span class="context-button-text js-context-button-text">
              <span class="mini-icon mini-icon-watching"></span>
              Watch
            </span>
          </li>
          <li class="selector-item js-navigation-item js-navigation-target ">
            <span class="mini-icon mini-icon-confirm"></span>
            <label>
              <input id="do_subscribed" name="do" type="radio" value="subscribed" />
              <h4>Watching</h4>
              <p>You will receive all notifications for this repository.</p>
            </label>
            <span class="context-button-text js-context-button-text">
              <span class="mini-icon mini-icon-unwatch"></span>
              Unwatch
            </span>
          </li>
          <li class="selector-item js-navigation-item js-navigation-target ">
            <span class="mini-icon mini-icon-confirm"></span>
            <label>
              <input id="do_ignore" name="do" type="radio" value="ignore" />
              <h4>Ignored</h4>
              <p>You will not receive notifications for this repository.</p>
            </label>
            <span class="context-button-text js-context-button-text">
              <span class="mini-icon mini-icon-mute"></span>
              Stop ignoring
            </span>
          </li>
        </ul>
      </div>
    </div>
  </div>
</form>
          </li>

          <li class="js-toggler-container js-social-container starring-container ">
            <a href="/sinlab-semester-2012/colorOfMind/unstar" class="minibutton js-toggler-target starred" data-remote="true" data-method="post" rel="nofollow">
              <span class="mini-icon mini-icon-star"></span>Unstar
            </a><a href="/sinlab-semester-2012/colorOfMind/star" class="minibutton js-toggler-target unstarred" data-remote="true" data-method="post" rel="nofollow">
              <span class="mini-icon mini-icon-star"></span>Star
            </a><a class="social-count js-social-count" href="/sinlab-semester-2012/colorOfMind/stargazers">0</a>
          </li>

              <li><a href="/sinlab-semester-2012/colorOfMind/fork" class="minibutton js-toggler-target fork-button lighter" rel="nofollow" data-method="post"><span class="mini-icon mini-icon-fork"></span>Fork</a><a href="/sinlab-semester-2012/colorOfMind/network" class="social-count">0</a>
              </li>


    </ul>

              <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
                <span class="repo-label"><span>public</span></span>
                <span class="mega-icon mega-icon-public-repo"></span>
                <span class="author vcard">
                  <a href="/sinlab-semester-2012" class="url fn" itemprop="url" rel="author">
                  <span itemprop="title">sinlab-semester-2012</span>
                  </a></span> /
                <strong><a href="/sinlab-semester-2012/colorOfMind" class="js-current-repository">colorOfMind</a></strong>
              </h1>
            </div>

            

  <ul class="tabs">
    <li><a href="/sinlab-semester-2012/colorOfMind" class="selected" highlight="repo_sourcerepo_downloadsrepo_commitsrepo_tagsrepo_branches">Code</a></li>
    <li><a href="/sinlab-semester-2012/colorOfMind/network" highlight="repo_network">Network</a></li>
    <li><a href="/sinlab-semester-2012/colorOfMind/pulls" highlight="repo_pulls">Pull Requests <span class='counter'>0</span></a></li>

      <li><a href="/sinlab-semester-2012/colorOfMind/issues" highlight="repo_issues">Issues <span class='counter'>0</span></a></li>

      <li><a href="/sinlab-semester-2012/colorOfMind/wiki" highlight="repo_wiki">Wiki</a></li>


    <li><a href="/sinlab-semester-2012/colorOfMind/graphs" highlight="repo_graphsrepo_contributors">Graphs</a></li>

      <li>
        <a href="/sinlab-semester-2012/colorOfMind/settings">Settings</a>
      </li>

  </ul>
  
<div class="tabnav">

  <span class="tabnav-right">
    <ul class="tabnav-tabs">
          <li><a href="/sinlab-semester-2012/colorOfMind/tags" class="tabnav-tab" highlight="repo_tags">Tags <span class="counter blank">0</span></a></li>
    </ul>
    
  </span>

  <div class="tabnav-widget scope">


    <div class="context-menu-container js-menu-container js-context-menu">
      <a href="#"
         class="minibutton bigger switcher js-menu-target js-commitish-button btn-branch repo-tree"
         data-hotkey="w"
         data-ref="master">
         <span><em class="mini-icon mini-icon-branch"></em><i>branch:</i> master</span>
      </a>

      <div class="context-pane commitish-context js-menu-content">
        <a href="#" class="close js-menu-close"><span class="mini-icon mini-icon-remove-close"></span></a>
        <div class="context-title">Switch branches/tags</div>
        <div class="context-body pane-selector commitish-selector js-navigation-container">
          <div class="filterbar">
            <input type="text" id="context-commitish-filter-field" class="js-navigation-enable js-filterable-field js-ref-filter-field" placeholder="Filter branches/tags">
            <ul class="tabs">
              <li><a href="#" data-filter="branches" class="selected">Branches</a></li>
                <li><a href="#" data-filter="tags">Tags</a></li>
            </ul>
          </div>

          <div class="js-filter-tab js-filter-branches">
            <div data-filterable-for="context-commitish-filter-field" data-filterable-type=substring>
                <div class="commitish-item branch-commitish selector-item js-navigation-item js-navigation-target selected">
                  <span class="mini-icon mini-icon-confirm"></span>
                  <h4>
                      <a href="/sinlab-semester-2012/colorOfMind/blob/master/README.md" class="js-navigation-open" data-name="master" rel="nofollow">master</a>
                  </h4>
                </div>
            </div>
            <div class="no-results">Nothing to show</div>


          </div>

            <div class="js-filter-tab js-filter-tags filter-tab-empty" style="display:none">
              <div data-filterable-for="context-commitish-filter-field" data-filterable-type=substring>
              </div>
              <div class="no-results">Nothing to show</div>
            </div>

        </div>
      </div><!-- /.commitish-context-context -->
    </div>
  </div> <!-- /.scope -->

  <ul class="tabnav-tabs">
    <li><a href="/sinlab-semester-2012/colorOfMind" class="selected tabnav-tab" highlight="repo_source">Files</a></li>
    <li><a href="/sinlab-semester-2012/colorOfMind/commits/master" class="tabnav-tab" highlight="repo_commits">Commits</a></li>
    <li><a href="/sinlab-semester-2012/colorOfMind/branches" class="tabnav-tab" highlight="repo_branches" rel="nofollow">Branches <span class="counter ">1</span></a></li>
  </ul>

</div>

  
  
  


            
          </div>
        </div><!-- /.repohead -->

        <div id="js-repo-pjax-container" class="container context-loader-container" data-pjax-container>
          


<!-- blob contrib key: blob_contributors:v21:3be4354932571417e59540d9f285ae5e -->
<!-- blob contrib frag key: views10/v8/blob_contributors:v21:3be4354932571417e59540d9f285ae5e -->

<div id="slider">


    <div class="frame-meta">

      <p title="This is a placeholder element" class="js-history-link-replace hidden"></p>
      <div class="breadcrumb">
        <span class='bold'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/sinlab-semester-2012/colorOfMind" class="js-slide-to" data-direction="back" itemscope="url"><span itemprop="title">colorOfMind</span></a></span></span> / <strong class="final-path">README.md</strong> <span class="js-zeroclipboard zeroclipboard-button" data-clipboard-text="README.md" data-copied-hint="copied!" title="copy to clipboard"><span class="mini-icon mini-icon-clipboard"></span></span>
      </div>

      <a href="/sinlab-semester-2012/colorOfMind/find/master" class="js-slide-to" data-hotkey="t" style="display:none">Show File Finder</a>

        
  <div class="commit file-history-tease">
    <img class="main-avatar" height="24" src="https://secure.gravatar.com/avatar/bd0cc000a21974697a24aa2cc928faa2?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
    <span class="author"><a href="/sinlab-semester-2012" rel="author">sinlab-semester-2012</a></span>
    <time class="js-relative-date" datetime="2013-01-06T15:21:28-08:00" title="2013-01-06 15:21:28">January 06, 2013</time>
    <div class="commit-title">
        <a href="/sinlab-semester-2012/colorOfMind/commit/b4da2f5b624d22b10833c65651540d60965c62aa" class="message">Update README.md</a>
    </div>

    <div class="participation">
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>1</strong> contributor</a></p>
      
    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2>Users on GitHub who have contributed to this file</h2>
      <ul class="facebox-user-list">
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/bd0cc000a21974697a24aa2cc928faa2?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/sinlab-semester-2012">sinlab-semester-2012</a>
        </li>
      </ul>
    </div>
  </div>


    </div><!-- ./.frame-meta -->

    <div class="frames">
      <div class="frame" data-permalink-url="/sinlab-semester-2012/colorOfMind/blob/b4da2f5b624d22b10833c65651540d60965c62aa/README.md" data-title="colorOfMind/README.md at master · sinlab-semester-2012/colorOfMind · GitHub" data-type="blob">

        <div id="files" class="bubble">
          <div class="file">
            <div class="meta">
              <div class="info">
                <span class="icon"><b class="mini-icon mini-icon-text-file"></b></span>
                <span class="mode" title="File Mode">file</span>
                  <span>60 lines (42 sloc)</span>
                <span>1.951 kb</span>
              </div>
              <ul class="button-group actions">
                  <li>
                        <a class="grouped-button minibutton bigger lighter"
                           href="/sinlab-semester-2012/colorOfMind/edit/master/README.md"
                           data-method="post" rel="nofollow" data-hotkey="e">Edit</a>
                  </li>
                <li><a href="/sinlab-semester-2012/colorOfMind/raw/master/README.md" class="minibutton grouped-button bigger lighter" id="raw-url">Raw</a></li>
                  <li><a href="/sinlab-semester-2012/colorOfMind/blame/master/README.md" class="minibutton grouped-button bigger lighter">Blame</a></li>
                <li><a href="/sinlab-semester-2012/colorOfMind/commits/master/README.md" class="minibutton grouped-button bigger lighter" rel="nofollow">History</a></li>
              </ul>
            </div>
              
  <div id="readme" class="blob instapaper_body">
    <article class="markdown-body entry-content" itemprop="mainContentOfPage"><h2>
<a name="colorofmind---a-brain-computer-guided-environment" class="anchor" href="#colorofmind---a-brain-computer-guided-environment"><span class="mini-icon mini-icon-link"></span></a>colorOfMind - A brain computer guided environment</h2>

<p>The purpose of this program is to map the state of mind of the user using the Emotiv EPOC headset with a RGB spot light.
The project is using the Emokit driver to get raw packets from the device and FFTW to process the signal.</p>

<p>For more infos:<br>
*The project, please check the wiki : <a href="https://github.com/sinlab-semester-2012/colorOfMind/wiki">https://github.com/sinlab-semester-2012/colorOfMind/wiki</a><br>
*Emotiv EPOC : <a href="http://en.wikipedia.org/wiki/Emotiv_Systems#Emotiv_EPOC">http://en.wikipedia.org/wiki/Emotiv_Systems#Emotiv_EPOC</a><br>
*SINLAB : <a href="http://www.sinlab.ch/">http://www.sinlab.ch/</a>  </p>

<h2>
<a name="required-libraries" class="anchor" href="#required-libraries"><span class="mini-icon mini-icon-link"></span></a>Required Libraries</h2>

<h1></h1>

<h3>
<a name="emokit" class="anchor" href="#emokit"><span class="mini-icon mini-icon-link"></span></a>Emokit</h3>

<p>*CMake - <a href="http://www.cmake.org">http://www.cmake.org</a><br>
*libmcrypt - <a href="https://sourceforge.net/projects/mcrypt/">https://sourceforge.net/projects/mcrypt/</a><br>
*hidapi - <a href="http://www.signal11.us/oss/hidapi/">http://www.signal11.us/oss/hidapi/</a>  </p>

<h3>
<a name="signal-processing" class="anchor" href="#signal-processing"><span class="mini-icon mini-icon-link"></span></a>Signal Processing</h3>

<p>*FFTW 3.3 - <a href="http://www.fftw.org/download.html">http://www.fftw.org/download.html</a>  </p>

<h3>
<a name="dmx-optional" class="anchor" href="#dmx-optional"><span class="mini-icon mini-icon-link"></span></a>Dmx (optional)</h3>

<p>*oscpack - Modified version already included in colorOfMind<br>
*Processing - <a href="http://processing.org/">http://processing.org/</a><br>
*DMXP512 - <a href="http://motscousus.com/stuff/2011-01_dmxP512/">http://motscousus.com/stuff/2011-01_dmxP512/</a>  </p>

<h3>
<a name="plot-optional" class="anchor" href="#plot-optional"><span class="mini-icon mini-icon-link"></span></a>Plot (optional)</h3>

<p>*Gnuplot - <a href="http://www.gnuplot.info/faq/faq.html">http://www.gnuplot.info/faq/faq.html</a></p>

<h2>
<a name="install" class="anchor" href="#install"><span class="mini-icon mini-icon-link"></span></a>Install</h2>

<h3>
<a name="linux" class="anchor" href="#linux"><span class="mini-icon mini-icon-link"></span></a>Linux</h3>

<p>Install the dependencies<br>
Follow the guide to install the depedencies if needed : <a href="https://github.com/sinlab-semester-2012/colorOfMind/wiki/How-to-Install-%3F">https://github.com/sinlab-semester-2012/colorOfMind/wiki/How-to-Install-%3F</a></p>

<p>Use the build.sh script and then the example you want :
"./bin/emotiv" to get the datas from the headset or a file<br>
"./bin/contact" to get the real-time value of the sensors<br>
"./bin/lightShow" to start the light show  </p>

<h3>
<a name="windows-" class="anchor" href="#windows-"><span class="mini-icon mini-icon-link"></span></a>Windows :</h3>

<p>Install the dependencies
Build the program using the cmake command
Should work not tested yet</p>

<h2>
<a name="platform-specifics-issues" class="anchor" href="#platform-specifics-issues"><span class="mini-icon mini-icon-link"></span></a>Platform Specifics Issues</h2>

<h1></h1>

<h4>
<a name="linux-1" class="anchor" href="#linux-1"><span class="mini-icon mini-icon-link"></span></a>Linux</h4>

<hr><p>"Due to the way hidapi works, the linux version of emokit can run using
either hidraw calls or libusb. These will require different udev rules
for each. We've tried to cover both (as based on hidapi's example udev
file), but your mileage may vary. If you have problems, please post
them to the github issues page (<a href="http://github.com/openyou/emokit/issues).">http://github.com/openyou/emokit/issues).</a>"</p></article>
  </div>

          </div>
        </div>
      </div>

      <a href="#jump-to-line" rel="facebox" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
      <div id="jump-to-line" style="display:none">
        <h2>Jump to Line</h2>
        <form accept-charset="UTF-8" class="js-jump-to-line-form">
          <input class="textfield js-jump-to-line-field" type="text">
          <div class="full-button">
            <button type="submit" class="classy">
              Go
            </button>
          </div>
        </form>
      </div>

    </div>
</div>

<div id="js-frame-loading-template" class="frame frame-loading large-loading-area" style="display:none;">
  <img class="js-frame-loading-spinner" src="https://a248.e.akamai.net/assets.github.com/images/spinners/octocat-spinner-128.gif?1347543527" height="64" width="64">
</div>


        </div>
      </div>
      <div class="context-overlay"></div>
    </div>

      <div id="footer-push"></div><!-- hack for sticky footer -->
    </div><!-- end of wrapper - hack for sticky footer -->

      <!-- footer -->
      <div id="footer">
  <div class="container clearfix">

      <dl class="footer_nav">
        <dt>GitHub</dt>
        <dd><a href="https://github.com/about">About us</a></dd>
        <dd><a href="https://github.com/blog">Blog</a></dd>
        <dd><a href="https://github.com/contact">Contact &amp; support</a></dd>
        <dd><a href="http://enterprise.github.com/">GitHub Enterprise</a></dd>
        <dd><a href="http://status.github.com/">Site status</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Applications</dt>
        <dd><a href="http://mac.github.com/">GitHub for Mac</a></dd>
        <dd><a href="http://windows.github.com/">GitHub for Windows</a></dd>
        <dd><a href="http://eclipse.github.com/">GitHub for Eclipse</a></dd>
        <dd><a href="http://mobile.github.com/">GitHub mobile apps</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Services</dt>
        <dd><a href="http://get.gaug.es/">Gauges: Web analytics</a></dd>
        <dd><a href="http://speakerdeck.com">Speaker Deck: Presentations</a></dd>
        <dd><a href="https://gist.github.com">Gist: Code snippets</a></dd>
        <dd><a href="http://jobs.github.com/">Job board</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Documentation</dt>
        <dd><a href="http://help.github.com/">GitHub Help</a></dd>
        <dd><a href="http://developer.github.com/">Developer API</a></dd>
        <dd><a href="http://github.github.com/github-flavored-markdown/">GitHub Flavored Markdown</a></dd>
        <dd><a href="http://pages.github.com/">GitHub Pages</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>More</dt>
        <dd><a href="http://training.github.com/">Training</a></dd>
        <dd><a href="https://github.com/edu">Students &amp; teachers</a></dd>
        <dd><a href="http://shop.github.com">The Shop</a></dd>
        <dd><a href="/plans">Plans &amp; pricing</a></dd>
        <dd><a href="http://octodex.github.com/">The Octodex</a></dd>
      </dl>

      <hr class="footer-divider">


    <p class="right">&copy; 2013 <span title="0.06039s from fe2.rs.github.com">GitHub</span> Inc. All rights reserved.</p>
    <a class="left" href="https://github.com/">
      <span class="mega-icon mega-icon-invertocat"></span>
    </a>
    <ul id="legal">
        <li><a href="https://github.com/site/terms">Terms of Service</a></li>
        <li><a href="https://github.com/site/privacy">Privacy</a></li>
        <li><a href="https://github.com/security">Security</a></li>
    </ul>

  </div><!-- /.container -->

</div><!-- /.#footer -->


    

    

<div id="keyboard_shortcuts_pane" class="instapaper_ignore readability-extra" style="display:none">
  <h2>Keyboard Shortcuts <small><a href="#" class="js-see-all-keyboard-shortcuts">(see all)</a></small></h2>

  <div class="columns threecols">
    <div class="column first">
      <h3>Site wide shortcuts</h3>
      <dl class="keyboard-mappings">
        <dt>s</dt>
        <dd>Focus command bar</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>?</dt>
        <dd>Bring up this help dialog</dd>
      </dl>
    </div><!-- /.column.first -->

    <div class="column middle" style='display:none'>
      <h3>Commit list</h3>
      <dl class="keyboard-mappings">
        <dt>j</dt>
        <dd>Move selection down</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>k</dt>
        <dd>Move selection up</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>c <em>or</em> o <em>or</em> enter</dt>
        <dd>Open commit</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>y</dt>
        <dd>Expand URL to its canonical form</dd>
      </dl>
    </div><!-- /.column.first -->

    <div class="column last js-hidden-pane" style='display:none'>
      <h3>Pull request list</h3>
      <dl class="keyboard-mappings">
        <dt>j</dt>
        <dd>Move selection down</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>k</dt>
        <dd>Move selection up</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt>o <em>or</em> enter</dt>
        <dd>Open issue</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt><span class="platform-mac">⌘</span><span class="platform-other">ctrl</span> <em>+</em> enter</dt>
        <dd>Submit comment</dd>
      </dl>
      <dl class="keyboard-mappings">
        <dt><span class="platform-mac">⌘</span><span class="platform-other">ctrl</span> <em>+</em> shift p</dt>
        <dd>Preview comment</dd>
      </dl>
    </div><!-- /.columns.last -->

  </div><!-- /.columns.equacols -->

  <div class="js-hidden-pane" style='display:none'>
    <div class="rule"></div>

    <h3>Issues</h3>

    <div class="columns threecols">
      <div class="column first">
        <dl class="keyboard-mappings">
          <dt>j</dt>
          <dd>Move selection down</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>k</dt>
          <dd>Move selection up</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>x</dt>
          <dd>Toggle selection</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>o <em>or</em> enter</dt>
          <dd>Open issue</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt><span class="platform-mac">⌘</span><span class="platform-other">ctrl</span> <em>+</em> enter</dt>
          <dd>Submit comment</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt><span class="platform-mac">⌘</span><span class="platform-other">ctrl</span> <em>+</em> shift p</dt>
          <dd>Preview comment</dd>
        </dl>
      </div><!-- /.column.first -->
      <div class="column last">
        <dl class="keyboard-mappings">
          <dt>c</dt>
          <dd>Create issue</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>l</dt>
          <dd>Create label</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>i</dt>
          <dd>Back to inbox</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>u</dt>
          <dd>Back to issues</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>/</dt>
          <dd>Focus issues search</dd>
        </dl>
      </div>
    </div>
  </div>

  <div class="js-hidden-pane" style='display:none'>
    <div class="rule"></div>

    <h3>Issues Dashboard</h3>

    <div class="columns threecols">
      <div class="column first">
        <dl class="keyboard-mappings">
          <dt>j</dt>
          <dd>Move selection down</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>k</dt>
          <dd>Move selection up</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>o <em>or</em> enter</dt>
          <dd>Open issue</dd>
        </dl>
      </div><!-- /.column.first -->
    </div>
  </div>

  <div class="js-hidden-pane" style='display:none'>
    <div class="rule"></div>

    <h3>Network Graph</h3>
    <div class="columns equacols">
      <div class="column first">
        <dl class="keyboard-mappings">
          <dt><span class="badmono">←</span> <em>or</em> h</dt>
          <dd>Scroll left</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt><span class="badmono">→</span> <em>or</em> l</dt>
          <dd>Scroll right</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt><span class="badmono">↑</span> <em>or</em> k</dt>
          <dd>Scroll up</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt><span class="badmono">↓</span> <em>or</em> j</dt>
          <dd>Scroll down</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>t</dt>
          <dd>Toggle visibility of head labels</dd>
        </dl>
      </div><!-- /.column.first -->
      <div class="column last">
        <dl class="keyboard-mappings">
          <dt>shift <span class="badmono">←</span> <em>or</em> shift h</dt>
          <dd>Scroll all the way left</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>shift <span class="badmono">→</span> <em>or</em> shift l</dt>
          <dd>Scroll all the way right</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>shift <span class="badmono">↑</span> <em>or</em> shift k</dt>
          <dd>Scroll all the way up</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>shift <span class="badmono">↓</span> <em>or</em> shift j</dt>
          <dd>Scroll all the way down</dd>
        </dl>
      </div><!-- /.column.last -->
    </div>
  </div>

  <div class="js-hidden-pane" >
    <div class="rule"></div>
    <div class="columns threecols">
      <div class="column first js-hidden-pane" >
        <h3>Source Code Browsing</h3>
        <dl class="keyboard-mappings">
          <dt>t</dt>
          <dd>Activates the file finder</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>l</dt>
          <dd>Jump to line</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>w</dt>
          <dd>Switch branch/tag</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>y</dt>
          <dd>Expand URL to its canonical form</dd>
        </dl>
      </div>
    </div>
  </div>

  <div class="js-hidden-pane" style='display:none'>
    <div class="rule"></div>
    <div class="columns threecols">
      <div class="column first">
        <h3>Browsing Commits</h3>
        <dl class="keyboard-mappings">
          <dt><span class="platform-mac">⌘</span><span class="platform-other">ctrl</span> <em>+</em> enter</dt>
          <dd>Submit comment</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>escape</dt>
          <dd>Close form</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>p</dt>
          <dd>Parent commit</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>o</dt>
          <dd>Other parent commit</dd>
        </dl>
      </div>
    </div>
  </div>

  <div class="js-hidden-pane" style='display:none'>
    <div class="rule"></div>
    <h3>Notifications</h3>

    <div class="columns threecols">
      <div class="column first">
        <dl class="keyboard-mappings">
          <dt>j</dt>
          <dd>Move selection down</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>k</dt>
          <dd>Move selection up</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>o <em>or</em> enter</dt>
          <dd>Open notification</dd>
        </dl>
      </div><!-- /.column.first -->

      <div class="column second">
        <dl class="keyboard-mappings">
          <dt>e <em>or</em> shift i <em>or</em> y</dt>
          <dd>Mark as read</dd>
        </dl>
        <dl class="keyboard-mappings">
          <dt>shift m</dt>
          <dd>Mute thread</dd>
        </dl>
      </div><!-- /.column.first -->
    </div>
  </div>

</div>

    <div id="markdown-help" class="instapaper_ignore readability-extra">
  <h2>Markdown Cheat Sheet</h2>

  <div class="cheatsheet-content">

  <div class="mod">
    <div class="col">
      <h3>Format Text</h3>
      <p>Headers</p>
      <pre>
# This is an &lt;h1&gt; tag
## This is an &lt;h2&gt; tag
###### This is an &lt;h6&gt; tag</pre>
     <p>Text styles</p>
     <pre>
*This text will be italic*
_This will also be italic_
**This text will be bold**
__This will also be bold__

*You **can** combine them*
</pre>
    </div>
    <div class="col">
      <h3>Lists</h3>
      <p>Unordered</p>
      <pre>
* Item 1
* Item 2
  * Item 2a
  * Item 2b</pre>
     <p>Ordered</p>
     <pre>
1. Item 1
2. Item 2
3. Item 3
   * Item 3a
   * Item 3b</pre>
    </div>
    <div class="col">
      <h3>Miscellaneous</h3>
      <p>Images</p>
      <pre>
![GitHub Logo](/images/logo.png)
Format: ![Alt Text](url)
</pre>
     <p>Links</p>
     <pre>
http://github.com - automatic!
[GitHub](http://github.com)</pre>
<p>Blockquotes</p>
     <pre>
As Kanye West said:

> We're living the future so
> the present is our past.
</pre>
    </div>
  </div>
  <div class="rule"></div>

  <h3>Code Examples in Markdown</h3>
  <div class="col">
      <p>Syntax highlighting with <a href="http://github.github.com/github-flavored-markdown/" title="GitHub Flavored Markdown" target="_blank">GFM</a></p>
      <pre>
```javascript
function fancyAlert(arg) {
  if(arg) {
    $.facebox({div:'#foo'})
  }
}
```</pre>
    </div>
    <div class="col">
      <p>Or, indent your code 4 spaces</p>
      <pre>
Here is a Python code example
without syntax highlighting:

    def foo:
      if not bar:
        return true</pre>
    </div>
    <div class="col">
      <p>Inline code for comments</p>
      <pre>
I think you should use an
`&lt;addr&gt;` element here instead.</pre>
    </div>
  </div>

  </div>
</div>


    <div id="ajax-error-message" class="flash flash-error">
      <span class="mini-icon mini-icon-exclamation"></span>
      Something went wrong with that request. Please try again.
      <a href="#" class="mini-icon mini-icon-remove-close ajax-error-dismiss"></a>
    </div>

    
    
    <span id='server_response_time' data-time='0.06170' data-host='fe2'></span>
    
  </body>
</html>

=======
"Due to the way hidapi works, the linux version of emokit can run using
either hidraw calls or libusb. These will require different udev rules
for each. We've tried to cover both (as based on hidapi's example udev
file), but your mileage may vary. If you have problems, please post
them to the github issues page (http://github.com/openyou/emokit/issues)."
>>>>>>> b4da2f5b624d22b10833c65651540d60965c62aa
